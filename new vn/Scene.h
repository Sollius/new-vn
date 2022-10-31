#pragma once

#include "MainHeader.h"

class Scene
{
private:
	sf::Sprite m_background = sf::Sprite();
	bool m_isShowInterface = false;
	sf::Sprite m_userInterface = sf::Sprite();
	std::vector<sf::Sprite> m_characters = std::vector<sf::Sprite>();

public:
	Scene();
	~Scene();
};

