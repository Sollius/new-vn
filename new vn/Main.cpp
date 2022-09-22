#include "MainHeader.h"
#include "Menu.h"
#include <math.h>
#include <cmath>

using namespace sf;

int main()
{
	bool debug = true, viewConsole = false;

	setlocale(LC_ALL, "Russian");

	RenderWindow window(VideoMode(1920, 1080), "SFML App");

	std::vector<sf::String> menuStrings = { "New game", "Load game", "Settings", "Exit" };

	Menu menu(
		4,
		Vector2f(100.f, 100.f),
		Vector2f(150.f, 250.f),
		menuStrings,
		Color::White,
		"left",
		"menu_bg.jpg"
	);

	std::vector<Text> texts;

	RectangleShape debugConsole = RectangleShape(Vector2f(200, 400.f));
	debugConsole.setFillColor(Color(0, 0, 0, 150));
	debugConsole.setPosition(1700, 100);

	Font font;
	font.loadFromFile("calibri.ttf");
	
	String mouseCoordsString, selectedItemString, menuItemColorString = menu.getItems().at(0).getTextFillColorString();
		std::to_string(menu.getItems().at(0).getText().getFillColor().r) + ", " +
		std::to_string(menu.getItems().at(0).getText().getFillColor().g) + ", " +
		std::to_string(menu.getItems().at(0).getText().getFillColor().b);
	Text mouseCoordsText = Text(mouseCoordsString, font, 20), menuItemColorText = Text(menuItemColorString, font, 20);
	Text selectedItemTexts[] = { Text(selectedItemString, font, 20), Text(selectedItemString, font, 20), Text(selectedItemString, font, 20), Text(selectedItemString, font, 20) };

	mouseCoordsText.setPosition(Vector2f(1705, 105));
	menuItemColorText.setPosition(Vector2f(1705, 125));
	for (int count = 0; count < menu.getItems().size(); count++)
	{
		selectedItemTexts[count].setPosition(Vector2f(1705, 145 + (count * 20)));
	}

	texts.push_back(mouseCoordsText);
	texts.push_back(menuItemColorText);
	for (auto& sit : selectedItemTexts)
	{
		texts.push_back(sit);
	}

	while (window.isOpen())
	{
		Event event;
		
		if (viewConsole)
		{
			/*
			std::cout << "mouse - " << Mouse::getPosition().x << "." << Mouse::getPosition().y << std::endl;
			for (auto& menuItem : menu.getItems())
			{
				std::cout <<
					menuItem.getId() << "g -" <<
					" h " << menuItem.getShape().getGlobalBounds().height <<
					" w " << menuItem.getShape().getGlobalBounds().width <<
					" t " << menuItem.getShape().getGlobalBounds().top <<
					" l " << menuItem.getShape().getGlobalBounds().left << std::endl <<
					menuItem.getId() << "l -" <<
					" h " << menuItem.getShape().getLocalBounds().height <<
					" w " << menuItem.getShape().getLocalBounds().width <<
					" t " << menuItem.getShape().getLocalBounds().top <<
					" l " << menuItem.getShape().getLocalBounds().left << std::endl;

			}
			*/
			
			mouseCoordsString = "mouse - " + std::to_string(Mouse::getPosition().x) + "," + std::to_string(Mouse::getPosition().y);
			mouseCoordsText.setString(mouseCoordsString);
		}

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

				if (event.key.code == Keyboard::Enter)
				{
					RenderWindow window(VideoMode(1024, 768), "SFML APP");
				}

				if (event.key.code == Keyboard::Tilde)
				{
					viewConsole = !viewConsole;
				}

				if (event.key.code == Keyboard::Hyphen)
				{
					for (auto& menuItem : menu.getItems())
					{
						menuItem.getTextForChanging().setFillColor(Color(
							menuItem.getText().getFillColor().r - 2,
							menuItem.getText().getFillColor().g - 2,
							menuItem.getText().getFillColor().b - 2));
					};

					menuItemColorString = menu.getItems().at(0).getTextFillColorString();
					texts[1].setString(menuItemColorString);
				}

				if (event.key.code == Keyboard::Add)
				{
					for (auto& menuItem : menu.getItems())
					{
						menuItem.getTextForChanging().setFillColor(Color(
							menuItem.getText().getFillColor().r + 2,
							menuItem.getText().getFillColor().g + 2,
							menuItem.getText().getFillColor().b + 2));
					}

					menuItemColorString = menu.getItems().at(0).getTextFillColorString();
					texts[1].setString(menuItemColorString);
				}
			}

			if (event.type == Event::MouseMoved)
			{
				for (auto& menuItem : menu.getItems())
				{
					if (menuItem.getText().getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y))
					{
						menuItem.getShape().setFillColor(Color(255, 100, 100, 200));
						if (viewConsole)
						{
							selectedItemString =
								"w" + std::to_string(lroundf(menuItem.getShape().getLocalBounds().width)) +
								" h" + std::to_string(lroundf(menuItem.getShape().getLocalBounds().height)) +
								" l" + std::to_string(lroundf(menuItem.getShape().getLocalBounds().left)) +
								" t" + std::to_string(lroundf(menuItem.getShape().getLocalBounds().top));

							texts[menuItem.getId() + 2].setString(selectedItemString);
						}
					}
					else
					{
						if (viewConsole)
						{
							selectedItemString.clear();

							texts[menuItem.getId() + 2].setString(selectedItemString);

						}
						menuItem.getShape().setFillColor(Color(255, 0, 0, 50));
					}
				}

			}
		}

		window.clear(Color::Blue);

		window.draw(menu.getSprite());

		for (auto& menuItem : menu.getItems())
		{
			if (debug)
			{
				window.draw(menuItem.getShape());
				window.draw(menu.getMainShape());
			}
			window.draw(menuItem.getText());
		}

		if (viewConsole)
		{
			window.draw(debugConsole);

			for (auto& text : texts)
			{
				window.draw(text);
			}

			window.draw(mouseCoordsText);
		}

		window.display();
	}

	return 0;
}