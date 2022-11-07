#pragma once
#include "SFML/Graphics.hpp"
class PlayingInterface
{
private:
	sf::Sprite m_panelSprite = sf::Sprite();
	std::vector<sf::Text> m_texts = std::vector<sf::Text>();

public:
	PlayingInterface();
	~PlayingInterface();
};

