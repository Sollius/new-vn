#include "Scene.h"
#include "TextActionType.h"

Scene::Scene() {};
Scene::~Scene() {}

Scene::Scene(Sprite background, std::vector<Sprite> characters) 
{
	m_background = background;
	m_characters = characters;
};

Scene::Scene(Player& player)
{
	m_player = player;
};

void Scene::setActions(std::vector<std::shared_ptr<BaseAction>> actions)
{
	m_actions = actions;
}

bool Scene::isActionsOver()
{
	if (m_actions.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Scene::setPlayer(Player& player)
{
	m_player = player;
}

Player Scene::display(RenderWindow& window, Clock clock)
{
	Event event;
	Time time = clock.restart();

	m_state = SceneState::ANIMATION;

	m_isShowInterface = false;
	bool isMusicAdded = false, isMusicPlaying = false;

	int musicActionsCount = 0;

	for (auto& action : m_actions)
	{
		if (action.get()->getActionType() == ActionType::MUSIC && action.get()->getMusicActionType() == MusicActionType::PLAY)
		{
			musicActionsCount++;
		}
	}

	if (m_musics.size() < musicActionsCount)
	{
		m_isNeedToPlayMusic = true;
	}

	while (m_state != SceneState::NONE)
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Escape:
						{
							if (!m_isAutoSkip)
							{
								if (m_state == SceneState::ANIMATION)
								{
									m_state = SceneState::AWAIT;
								}
								else
								{
									m_state = SceneState::NONE;
								}
							}
							else
							{
								m_actions.clear();
								m_texts.clear();

								return m_player;
								break;
							}
						}
					}

					break;
				}
				case sf::Event::MouseMoved:
				{
					for (auto& action : m_actions)
					{
						if (action.get()->getActionType() == ActionType::OPTION)
						{
							action.get()->setHovered(Vector2f(Mouse::getPosition(window)));
						}
					}

					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					for (auto& action : m_actions)
					{
						if (action.get()->getActionType() == ActionType::OPTION)
						{
							m_player.addFlag({ action.get()->getSelectionName(), action.get()->getSelectedOptionNumber(Vector2f(Mouse::getPosition(window))) });

							m_actions.clear();
							m_texts.clear();
							m_buttons.clear();

							return m_player;
						    break;
						}
					}
				}
			}
		}

		m_characters.clear();
		int finishedActionsCount = 0;
	
		for (auto& action : m_actions)
		{
			ActionExecutor& actionExecutor = *action;

			switch (m_state)
			{
				case SceneState::NONE:
				{
					break;
				}
				case SceneState::ANIMATION:
				{
					////////////////
					//////////////// проверка на музыкальный тип только для музыкальный действий !!!!!!!!!!!!
					////////////////
 					if (action.get()->getActionType() == ActionType::MUSIC && actionExecutor.getMusicActionType() == MusicActionType::PLAY)
					{
						////if (m_isNeedToPlayMusic)
						////{
						////	this->addMusic(actionExecutor.getMusicId(), actionExecutor.getMusicFileName(), 0);
						////	m_isNeedToPlayMusic = false;
						////}

						if (!isMusicAdded)
						{
							addMusicFile(actionExecutor.getMusicFileName());
							isMusicAdded = true;
						}
					}
					else
					{
						actionExecutor.execute(clock, time);

						if (action.get()->getActionType() == ActionType::TEXT || action.get()->getActionType() == ActionType::OPTION)
						{
							m_isShowInterface = true;
						}
					}

					break;
				}
				case SceneState::TEXT_DISPLAYING:
				{
					if (action.get()->getActionType() == ActionType::TEXT)
					{
					}
					
					if (action.get()->getActionType() == ActionType::OPTION)
					{
					}

					break;
				}
				case SceneState::AWAIT:
				{
					action.get()->setSkipped();
					break;
				}
			}

			switch (action.get()->getActionType())
			{
				case ActionType::NONE:
				{
					throw __uncaught_exception;
					exit(1);
					break;
				}
				case ActionType::BACKGROUND:
				{
					setBackground(actionExecutor.getSprite());
					break;
				}
				case ActionType::CHARACTER:
				{
					m_characters.push_back(actionExecutor.getSprite());
					break;
				}
				case ActionType::TEXT:
				{
					if (actionExecutor.getTextActionType() == TextActionType::MOVING_OUT)
					{
						m_isShowInterface = false;
					}

					m_texts.push_back(actionExecutor.getText());
					break;
				}
				case ActionType::OPTION:
				{
					for (auto& button : actionExecutor.getButtons())
					{
						m_buttons.push_back(std::get<0>(button));
						m_texts.push_back(std::get<1>(button));
					}
					break;
				}
				case ActionType::MUSIC:
				{
					switch (actionExecutor.getMusicActionType())
					{
						case MusicActionType::PLAY:
						{
							////if (std::get<1>(music).getStatus() != sf::SoundSource::Playing)
							if (!isMusicPlaying)
							{
								if (m_music.getStatus() != sf::SoundSource::Playing)
								{
									m_music.play();
									isMusicPlaying = true;

									auto status = m_music.getStatus();
								}
								else
								{
									throw __uncaught_exception;
									std::cout << "Ошибка состояния музыкального потока" << std::endl;
								}
							}

							break;
						}
						case MusicActionType::PAUSE:
						{
							if (m_music.getStatus() == sf::SoundSource::Playing)
							{
								m_music.pause();
							}
							else
							{
								throw __uncaught_exception;
								std::cout << "Ошибка состояния музыкального потока" << std::endl;
							}

							break;
						}
						case MusicActionType::STOP:
						{
							if (m_music.getStatus() == sf::SoundSource::Playing)
							{
								m_music.stop();
							}
							else
							{
								throw __uncaught_exception;
								std::cout << "Ошибка состояния музыкального потока" << std::endl;
							}

							break;
						}
						default:
						{
							throw __uncaught_exception;
							std::cout << "Ошибка непредвиденного или неопределённого типа музыкального действия" << std::endl;
							exit(1);
						}
					}
					////for (auto& music : m_musics)
					////{
					////	if (actionExecutor.getMusicId() != std::get<0>(music))
					////	{
					////		throw __uncaught_exception;
					////		std::cout << "Ошибка несоответствия номера действия и музыки" << std::endl;
					////		exit(1);
					////	}

					////	switch (actionExecutor.getMusicActionType())
					////	{
					////		case MusicActionType::PLAY:
					////		{
					////			////if (std::get<1>(music).getStatus() != sf::SoundSource::Playing)
					////			if (m_music.getStatus() != sf::SoundSource::Playing)
					////			{
					////				////std::get<1>(music).play();
					////				m_music.play();
					////			}
					////			else
					////			{
					////				throw __uncaught_exception;
					////				std::cout << "Ошибка состояния музыкального потока" << std::endl;
					////			}

					////			break;
					////		}
					////		case MusicActionType::PAUSE:
					////		{
					////			if (std::get<1>(music).getStatus() == sf::SoundSource::Playing)
					////			{
					////				std::get<1>(music).pause();
					////			}
					////			else
					////			{
					////				throw __uncaught_exception;
					////				std::cout << "Ошибка состояния музыкального потока" << std::endl;
					////			}

					////			break;
					////		}
					////		case MusicActionType::STOP:
					////		{
					////			if (std::get<1>(music).getStatus() == sf::SoundSource::Playing)
					////			{
					////				std::get<1>(music).stop();
					////			}
					////			else
					////			{
					////				throw __uncaught_exception;
					////				std::cout << "Ошибка состояния музыкального потока" << std::endl;
					////			}

					////			break;
					////		}
					////		default:
					////		{
					////			throw __uncaught_exception;
					////			std::cout << "Ошибка непредвиденного или неопределённого типа музыкального действия" << std::endl;
					////			exit(1);
					////		}
					////	}
					////}

					break;
				}
				default:
				{
					throw __uncaught_exception;
					std::cout << "Ошибка непредвиденного или неопределённого типа действия" << std::endl;
					exit(1);
				}
			}

			if (action.get()->getState())
			{
				finishedActionsCount++;
			}
		}

		window.clear(Color::Black);

		window.draw(m_background);

		for (auto& character : m_characters)
		{
			window.draw(character);
		}

		if (m_isShowInterface)
		{
			window.draw(m_userInterface);

			if (!m_buttons.empty())
			{
				for (auto& button : m_buttons)
				{
					window.draw(button);
				}
			}

			for (auto& text : m_texts)
			{
				window.draw(text);
			}
		}

		window.display();

		if (finishedActionsCount == m_actions.size())
		{
			if (m_state == SceneState::NONE)
			{
				m_actions.clear();
				m_texts.clear();
				m_buttons.clear();

				return m_player;
			}

			m_state = SceneState::AWAIT;
		}
	}
}

void Scene::pushAction(Sprite sprite)
{
	m_characters.push_back(sprite);
}

void Scene::setBackground(Sprite sprite)
{
	m_background = sprite;
}

void Scene::setUserInterface(sf::RectangleShape userInterface)
{
	m_userInterface = userInterface;
}

Sprite Scene::getBackground()
{
	return m_background;
}

RectangleShape Scene::getUserInterface()
{
	return m_userInterface;
}

RectangleShape& Scene::getUserInterfaceForChanging()
{
	return m_userInterface;
}

Player& Scene::getPlayer()
{
	return m_player;
}

void Scene::setMusics(std::vector<std::string> musicsFileNames)
{
	for (auto& musicFileName : musicsFileNames)
	{
		sf::Music newMusic = sf::Music();
		newMusic.openFromFile(musicFileName);
		newMusic.setLoop(true);
	}
}

std::vector<std::tuple<int, sf::Music&>> Scene::getMusics()
{
	return m_musics;
}

void Scene::addMusic(int id, std::string musicFileName, float startTimeInSecs = 0.f)
{
	//// TODO: возможно необходимо сделать возможность добавлять более одного трека в сцену
	////m_musics.push_back(musicKeyValue);

	sf::Music newMusic = sf::Music();
	newMusic.openFromFile(musicFileName);
	newMusic.setPlayingOffset(sf::seconds(startTimeInSecs));
	newMusic.setLoop(true);

	sf::Music& musicRef = newMusic;

	m_musics.push_back({ id, musicRef });
}

void Scene::addMusicFile(sf::String musicFileName)
{
	m_music.openFromFile(musicFileName);
	m_music.setLoop(true);
}