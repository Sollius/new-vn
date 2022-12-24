#include "Scene.h"

Scene::Scene() {};

Scene::Scene(Sprite background, std::vector<Sprite> characters) 
{
	m_background = background;
	m_characters = characters;
};

Scene::~Scene() {};

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

void Scene::display(RenderWindow& window, Clock clock)
{
	Event event;
	Time time = clock.restart();

	m_state = SceneState::ANIMATION;

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

							return;
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
					if (action.get()->getActionType() == ActionType::BACKGROUND ||
						action.get()->getActionType() == ActionType::CHARACTER)
						{
							actionExecutor.execute(clock, time);
						}
					break;
				}
				case SceneState::TEXT_DISPLAYING:
				{
					if (action.get()->getActionType() == ActionType::TEXT)
					{
						actionExecutor.execute(clock, time);
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
					m_texts.push_back(actionExecutor.getText());
					break;
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

				return;
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