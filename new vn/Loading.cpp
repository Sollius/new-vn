#include "Loading.h"

Loading::Loading() {};

void Loading::showLoadingBarInCenter(sf::RenderWindow& window, sf::Vector2f loadingShapeSize, float outlineThickness, sf::Clock clock)
{
	if (window.isOpen())
	{
		m_shapes[0].setSize(loadingShapeSize);
		m_shapes[0].setPosition(
			sf::Vector2f((window.getSize().x / 2) - (m_shapes[0].getGlobalBounds().width / 2),
				(window.getSize().y / 2) - (m_shapes[0].getGlobalBounds().height / 2)));
		m_shapes[0].setFillColor(sf::Color(100, 100, 100, 150));
		m_shapes[0].setOutlineColor(sf::Color(50, 50, 50, 200));
		m_shapes[0].setOutlineThickness(outlineThickness);

		m_shapes[1].setSize(sf::Vector2f(0, loadingShapeSize.y));
		m_shapes[1].setPosition(
			sf::Vector2f((window.getSize().x / 2) - (m_shapes[0].getGlobalBounds().width / 2) + m_shapes[0].getOutlineThickness(),
				(window.getSize().y / 2) - (m_shapes[0].getGlobalBounds().height / 2) + m_shapes[0].getOutlineThickness()));
		m_shapes[1].setFillColor(sf::Color(0, 150, 0, 200));
		m_shapes[1].setOutlineThickness(0);
	}

	sf::Time time = clock.restart();

	while (m_loadingProgress <= m_shapes[0].getSize().x)
	{
		time = clock.getElapsedTime();

		if (time.asMilliseconds() >= 1 && m_loadingProgress <= m_shapes[0].getSize().x)
		{
			increaseProgressBar();
			time = clock.restart();
			m_shapes[1].setSize(sf::Vector2f(m_loadingProgress, m_shapes[1].getSize().y));
		}

		window.clear(sf::Color::Black);

		for (auto& loadingShape : m_shapes)
		{
			window.draw(loadingShape);
		}

		window.display();
	}
}

Loading::Loading(int procentOfProgress)
{

}

void Loading::increaseProgressBar()
{
	m_loadingProgress += 0.1;
}