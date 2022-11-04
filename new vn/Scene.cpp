#include "Scene.h"

Scene::Scene() {};

Scene::Scene(Sprite background, std::vector<Sprite> characters) 
{
	m_background = background;
	m_characters = characters;
};

Scene::~Scene() {};

void Scene::display(RenderWindow& window, Clock clock)
{
	window.clear(Color::Black);

	window.draw(m_background);

	for (auto& character : m_characters)
	{
		window.draw(character);
	}

	window.display();
}

void Scene::pushAction(Sprite sprite)
{
	m_characters.push_back(sprite);
}

void Scene::setBackground(Sprite sprite)
{
	m_background = sprite;
}