#pragma once

#include <array>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Main.hpp"

class Loading
{
private:
	std::array<sf::RectangleShape, 2> m_shapes = std::array<sf::RectangleShape, 2>();
	float m_loadingProgress = 0.f;

public:
	Loading();

	Loading(int procentOfProgress);

	void showLoadingBarInCenter(sf::RenderWindow& window, sf::Vector2f loadingShapeSize, float outlineThickness, sf::Clock clock);

	void increaseProgressBar();
};