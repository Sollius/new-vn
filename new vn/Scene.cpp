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

	bool isSkipped = false;

	while (!m_actions.empty())
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
						if (!isSkipped)
						{
							isSkipped = true;
						}
						else
						{
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

			actionExecutor.execute(clock, time);

			if (action.get()->getActionType() == ActionType::BACKGROUND)
			{
				setBackground(actionExecutor.getSprite());
			}
			else
			{
				m_characters.push_back(actionExecutor.getSprite());
			}

			if (action.get()->getState())
			{
				finishedActionsCount++;
			}

			if (isSkipped)
			{
				time = seconds(3600);
				while (!action.get()->getState())
				{
					actionExecutor.execute(clock, time);
				}

				if (action.get()->getActionType() == ActionType::BACKGROUND)
				{
					setBackground(actionExecutor.getSprite());
				}
				else
				{
					m_characters.push_back(actionExecutor.getSprite());
				}
			}
		}

		window.clear(Color::Black);

		window.draw(m_background);

		for (auto& character : m_characters)
		{
			window.draw(character);
		}

		window.display();

		if (finishedActionsCount == m_actions.size() && isSkipped)
		{
			m_actions.clear();

			return;
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

Sprite Scene::getBackground()
{
	return m_background;
}