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

void Scene::addMusicFile(std::string musicFileName)
{
	m_music.openFromFile(musicFileName);
	m_music.setLoop(true);
}

void Scene::addMusicFileByInfo(std::tuple<std::string, float, float, float> musicFileInfo)
{
	m_music.openFromFile(std::get<0>(musicFileInfo));

	if (std::get<3>(musicFileInfo) > 0.f)
	{
		m_music.setLoopPoints(sf::Music::TimeSpan(sf::seconds(std::get<2>(musicFileInfo)), sf::seconds(std::get<3>(musicFileInfo))));
	}

	m_music.setLoop(true);

	if (std::get<1>(musicFileInfo) > 0.f)
	{
		m_music.setPlayingOffset(sf::seconds(std::get<1>(musicFileInfo)));
	}
}

Player Scene::display(RenderWindow& window, Clock clock)
{
	Event event;
	Time time = clock.restart();

	m_state = SceneState::ANIMATION;

	m_isShowInterface = false;
	bool isMusicAdded = false, isMusicPlaying = false;

	while (m_state != SceneState::NONE)
	{
		//////////////////////////////
		////// EVENT DIFINITION //////
		//////////////////////////////

		while (window.pollEvent(event))
		{
			switch (m_state)
			{
				case SceneState::NONE:
				{
					////throw __uncaught_exception;
					////std::cout << "Неопределённый этап рендера изображения" << std::endl;
					////exit(1);
					////break;
				}
				case SceneState::ANIMATION:
				{
					if (event.type == sf::Event::MouseButtonPressed)
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

					break;
				}
				case SceneState::TEXT_DISPLAYING:
				{
					break;
				}
				case SceneState::ANSWER_AWAITING:
				{
					for (auto& action : m_actions)
					{
						if (event.type == sf::Event::MouseButtonPressed)
						{
							if (action.get()->getActionType() == ActionType::OPTION)
							{
								for (auto& button : m_buttons)
								{
									if (button.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
									{
										m_player.addFlag({ action.get()->getSelectionName(), action.get()->getSelectedOptionNumber(Vector2f(Mouse::getPosition(window))) });

										m_actions.clear();
										m_texts.clear();
										m_buttons.clear();

										return m_player;
									}
								}
							}
						}

						if (event.type == sf::Event::MouseMoved)
						{
							for (auto& action : m_actions)
							{
								if (action.get()->getActionType() == ActionType::OPTION)
								{
									action.get()->setHovered(Vector2f(Mouse::getPosition(window)));
								}
							}
						}
					}

					break;
				}
				case SceneState::AWAIT:
				{
					if (event.type == sf::Event::MouseButtonPressed)
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

					break;
				}
				default:
				{
					throw __uncaught_exception;
					std::cout << "Ошибка в определении этапа рендера изображения" << std::endl;
					exit(1);
					break;
				}
			}

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
							//// TODO: окошко меню
						}
					}

					break;
				}
				case sf::Event::MouseMoved:
				{
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					break;
				}
			}
		}

		///////////////////////////////////
		///// цикл перебора действий //////
		///////////////////////////////////

		m_characters.clear();
		int finishedActionsCount = 0;
	
		for (auto& action : m_actions)
		{
			ActionExecutor& actionExecutor = *action;

			////// добавление музыки
			if (action.get()->getActionType() == ActionType::MUSIC && actionExecutor.getMusicActionType() == MusicActionType::PLAY)
			{
				////if (m_isNeedToPlayMusic)
				////{
				////	this->addMusic(actionExecutor.getMusicId(), actionExecutor.getMusicFileName(), 0);
				////	m_isNeedToPlayMusic = false;
				////}

				if (!isMusicAdded)
				{
					addMusicFileByInfo(actionExecutor.getMusicFileInfo());
					isMusicAdded = true;
				}
			}

			if (action.get()->getActionType() == ActionType::SOUND)
			{
				if (actionExecutor.getSoundActionType() == SoundActionType::PLAY)
				{
					bool isNeedToAddSound = true;

					for (auto& sound : m_sounds)
					{
						if (std::get<0>(sound) == actionExecutor.getSoundId())
						{
							isNeedToAddSound = false;
						}
					}

					if (isNeedToAddSound)
					{
						m_sounds.push_back(std::make_tuple(actionExecutor.getSoundId(), sf::Sound(actionExecutor.getSoundBuffer()), false));
					}
				}
			}

			switch (m_state)
			{
				case SceneState::NONE:
				{
					break;
				}
				case SceneState::ANIMATION:
				{
					if (action.get()->getActionType() == ActionType::TEXT || action.get()->getActionType() == ActionType::OPTION && action.get()->getActionType() != ActionType::MUSIC)
					{
						m_isShowInterface = true;
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
				case SceneState::ANSWER_AWAITING:
				{
					break;
				}
				default:
				{
					throw __uncaught_exception;
					std::cout << "Ошибка при определении стадии рендера изображения" << std::endl;
					exit(1);
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
					actionExecutor.execute(clock, time);

					setBackground(actionExecutor.getSprite());
					break;
				}
				case ActionType::CHARACTER:
				{
					actionExecutor.execute(clock, time);

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

						m_state = SceneState::ANSWER_AWAITING;
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

					break;
				}
				case ActionType::SOUND:
				{
					for (auto& sound : m_sounds)
					{
						if (!std::get<2>(sound))
						{
							std::get<1>(sound).play();

							std::get<2>(sound) = true;
						}
					}

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

		//////////////////////
		///// DISPLAYING /////
		//////////////////////

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
				m_sounds.clear();

				return m_player;
			}

			m_state = SceneState::AWAIT;
		}
	}

	return m_player;
}