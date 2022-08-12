#include "MainHeader.h"
#include "Menu.h"

using namespace sf;

int main()
{
	setlocale(LC_ALL, "Russian");

	RenderWindow window(VideoMode(1920, 1080), "SFML App");

	std::vector<sf::String> menuStrings = { "New game", "Load game", "Settings", "Exit" };

	Menu menu(
		4,
		Vector2f(1600, 400.f),
		Vector2f(200.f, 140),
		menuStrings,
		"right"
	);

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

		window.draw(menu.getMainShape());
		for (auto menuItem : menu.getItems())
		{
			window.draw(menuItem.getShape());
			window.draw(menuItem.getText());
		}

		window.display();
	}

	return 0;
}