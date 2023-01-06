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
	//// TODO: �������� ���������� ������� ����������� ��������� ����� ������ ����� � �����
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

	////int musicActionsCount = 0;

	////for (auto& action : m_actions)
	////{
	////	if (action.get()->getActionType() == ActionType::MUSIC && action.get()->getMusicActionType() == MusicActionType::PLAY)
	////	{
	////		musicActionsCount++;
	////	}
	////}

	////if (m_musics.size() < musicActionsCount)
	////{
	////	m_isNeedToPlayMusic = true;
	////}

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

			////////////////
			//////////////// �������� �� ����������� ��� ������ ��� ����������� �������� !!!!!!!!!!!!
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
					addMusicFileByInfo(actionExecutor.getMusicFileInfo());
					isMusicAdded = true;
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
					actionExecutor.execute(clock, time);

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
									std::cout << "������ ��������� ������������ ������" << std::endl;
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
								std::cout << "������ ��������� ������������ ������" << std::endl;
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
								std::cout << "������ ��������� ������������ ������" << std::endl;
							}

							break;
						}
						default:
						{
							throw __uncaught_exception;
							std::cout << "������ ��������������� ��� �������������� ���� ������������ ��������" << std::endl;
							exit(1);
						}
					}

					////for (auto& music : m_musics)
					////{
					////	if (actionExecutor.getMusicId() != std::get<0>(music))
					////	{
					////		throw __uncaught_exception;
					////		std::cout << "������ �������������� ������ �������� � ������" << std::endl;
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
					////				std::cout << "������ ��������� ������������ ������" << std::endl;
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
					////				std::cout << "������ ��������� ������������ ������" << std::endl;
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
					////				std::cout << "������ ��������� ������������ ������" << std::endl;
					////			}

					////			break;
					////		}
					////		default:
					////		{
					////			throw __uncaught_exception;
					////			std::cout << "������ ��������������� ��� �������������� ���� ������������ ��������" << std::endl;
					////			exit(1);
					////		}
					////	}
					////}

					break;
				}
				default:
				{
					throw __uncaught_exception;
					std::cout << "������ ��������������� ��� �������������� ���� ��������" << std::endl;
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

	return m_player;
}