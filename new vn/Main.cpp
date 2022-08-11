#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

int main()
{
	setlocale(LC_ALL, "Rus");

	RenderWindow window(VideoMode(1920, 1080), "SFML App");

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		window.clear(Color::Blue);

		window.display();

	}

	return 0;
}