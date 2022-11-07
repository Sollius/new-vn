#pragma once

#include <array>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Main.hpp"

class Loading
{
private:
	std::array<sf::RectangleShape, 2> m_shapes = std::array<sf::RectangleShape, 2>();
	float m_progressInPercents = 0.f;
	float m_endPointInPercents = 100.f;
	int m_updateRateInMs = 1;
	float m_progressIncreasingStep = 2.f;
	sf::Color m_outShapeFillColor = sf::Color(100, 100, 100, 150);
	sf::Color m_outShapeThicknessColor = sf::Color(50, 50, 50, 200);
	sf::Color m_inShapeFillColor = sf::Color(0, 150, 0, 200);

public:
	Loading(sf::Color outShapeFillColor, sf::Color outShapeThicknessColor, sf::Color inShapeFillColor);

	void showLoadingBarInCenter(
		sf::RenderWindow& window,
		sf::Vector2f loadingShapeSize,
		float outlineThickness,
		sf::Clock clock
	);

	void showLoadingBarInCenterWithStartProgress(
		sf::RenderWindow& window,
		sf::Vector2f loadingShapeSize,
		float outlineThickness,
		sf::Clock clock,
		float startPercentsOfProgress
	);

	void showLoadingBarInCenterWithEndPoint(
		sf::RenderWindow& window,
		sf::Vector2f loadingShapeSize,
		float outlineThickness,
		sf::Clock clock,
		float endPointInPercents
	);

	void showLoadingBarInCenterWithStartProgressAndEndPoint(
		sf::RenderWindow& window,
		sf::Vector2f loadingShapeSize,
		float outlineThickness,
		sf::Clock clock,
		float startPercentsOfProgress,
		float endPointInPercents
	);

	void increaseProgressBar();
};