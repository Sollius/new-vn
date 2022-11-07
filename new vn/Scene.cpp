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
	int finishedActionsCount = 0;
	while (true)
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
					return;
					break;
				}
			}
		}
	
		for (auto& action : m_actions)
		{
			ActionExecutor& actionExecutor = *action;

			window.clear(Color::Black);

			actionExecutor.execute(clock);
			window.draw(actionExecutor.getSprite());

			window.display();

			if (action.get()->getState())
			{
				finishedActionsCount++;
			}

			if (finishedActionsCount == m_actions.size())
			{
				m_actions.clear();
				return;
			}
		}

		////window.draw(m_background);

		////for (auto& character : m_characters)
		////{
		////	window.draw(character);
		////}


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