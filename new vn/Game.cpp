#include "Game.h"

#include "MainHeader.h"



int Game(sf::RenderWindow& window, DebugConsole debugConsole, bool debug, Clock clock)
{
	if (!window.isOpen())
	{
		return 0;
	}

	Loading loading;
	loading.showLoadingBarInCenter(window, Vector2f(200, 20), 4.f, clock);

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

		window.display();
	}

	return 0;
}