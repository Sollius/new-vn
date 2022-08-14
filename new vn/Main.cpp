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
		Vector2f(100.f, 100.f),
		Vector2f(120.f, 200),
		menuStrings,
		"right",
		"menu_bg.jpg"
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

			if (event.type == Event::MouseMoved)
			{
			int count = 0;
				for (auto& menuItem : menu.getItems())
				{
					count++;
					menuItem.getShape().getGlobalBounds().left;

					if (menuItem.getShape().getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y))
					{
						menuItem.getShape().setFillColor(Color(255, 100, 100, 200));
					}
					else
					{
						std::cout << "shape " << count << " DONT countains" << std::endl;
						menuItem.getShape().setFillColor(Color(255, 0, 0, 50));
					}
				}
			}
		}

		window.clear(Color::Blue);

		window.draw(menu.getSprite());
		window.draw(menu.getMainShape());
		for (auto& menuItem : menu.getItems())
		{
			window.draw(menuItem.getShape());
			window.draw(menuItem.getText());
		}

		window.display();
	}

	return 0;
}