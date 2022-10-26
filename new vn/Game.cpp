#include "Game.h"

#include "MainHeader.h"

int Game(sf::RenderWindow& window)
{
	sf::RectangleShape loadingShape = sf::RectangleShape(Vector2f(400, 30));
	loadingShape.setPosition(
		Vector2f((window.getSize().x / 2) - (loadingShape.getGlobalBounds().width / 2),
			(window.getSize().y / 2) - (loadingShape.getGlobalBounds().height / 2)));
	loadingShape.setFillColor(Color(100, 100, 100, 150));
	loadingShape.setOutlineColor(Color(50, 50, 50, 200));
	loadingShape.setOutlineThickness(2);

	sf::RectangleShape loadingProgressShape = sf::RectangleShape(Vector2f(0, 30));
	loadingProgressShape.setPosition(
		Vector2f((window.getSize().x / 2) - (loadingShape.getGlobalBounds().width / 2) + 2,
			(window.getSize().y / 2) - (loadingShape.getGlobalBounds().height / 2) + 2));
	loadingProgressShape.setFillColor(Color(0, 150, 0, 200));
	loadingProgressShape.setOutlineThickness(0);

	Clock clock;
	Time time = clock.restart();

	int loadingX = 0;

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					return 0;
					break;
				}
			}
		}

		window.clear(Color::Black);

		time = clock.getElapsedTime();
		if (time.asMilliseconds() >= 10 && loadingX <= loadingShape.getSize().x)
		{
			time = clock.restart();
			loadingProgressShape.setSize(Vector2f((float)++loadingX, loadingProgressShape.getSize().y));
		} 
		else
			if (loadingX > loadingShape.getSize().x)
			{
				return 0;
			}

		window.draw(loadingShape);
		window.draw(loadingProgressShape);
		window.display();
	}

	return 0;
}