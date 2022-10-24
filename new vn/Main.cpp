#include "MainHeader.h"
#include "MenuBlock.h"
#include <math.h>
#include <cmath>

using namespace sf;

int main()
{
	setlocale(LC_ALL, "Russian");

	bool debug = false;

	Font defaultFont;
	defaultFont.loadFromFile("calibri.ttf");

	Uint32 windowStyle;
	Vector2i windowSize;

	if (debug)
	{
		windowSize = Vector2i(1920, 1080);
		windowStyle = Style::Default;
	}
	else
	{
		windowSize = Vector2i(1920, 1080);
		windowStyle = Style::Fullscreen;
	}

	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "SFML App", windowStyle);

	MenuBlock menu(
		4,
		Vector2f(100.f, 100.f),
		Vector2f(150.f, 250.f),
		{ String(L"New game"), String("Load game"), String("Settings"), String("Exit") },
		Color(255, 255, 255, 200),
		"left",
		"menu_bg.jpg"
	);

	DebugConsole console
	(
		RectangleShape(Vector2f(400.f, 400.f)),
		Vector2f(1500, 100),
		Color(0, 0, 0, 150),
		std::vector<Text>
			{
				Text(String(""), defaultFont, 20),
				Text(String(""), defaultFont, 20),
				Text(String(""), defaultFont, 20),
				Text(String(""), defaultFont, 20),
				Text(String(""), defaultFont, 20),
				Text(String(""), defaultFont, 20),
			}
	);

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
					window.close();
					break;
				case Keyboard::Enter:
					break;
				case Keyboard::Tilde:
					console.switchShowingConsole();
					break;
				}
			case Event::MouseMoved:
				menu.setItemsBoldIfHovered(window);

				for (auto& menuItem : menu.getItems())
				{
					menuItem.getShape().setFillColor(Color(255, 100, 100, 200));

					if (console.showingConsole())
					{
						console.getTextsForChanging().at(2 + menuItem.getId()).setString(
							"g - " + std::to_string(lroundf(menuItem.getText().getGlobalBounds().width)) +
							" " + std::to_string(lroundf(menuItem.getText().getGlobalBounds().height)) +
							" " + std::to_string(lroundf(menuItem.getText().getGlobalBounds().left)) +
							" " + std::to_string(lroundf(menuItem.getText().getGlobalBounds().top)) +
							"; l - " + std::to_string(lroundf(menuItem.getText().getLocalBounds().width)) +
							" " + std::to_string(lroundf(menuItem.getText().getLocalBounds().height)) +
							" " + std::to_string(lroundf(menuItem.getText().getLocalBounds().left)) +
							" " + std::to_string(lroundf(menuItem.getText().getLocalBounds().top)));
					}
				}

				break;
			}

			for (auto& item : menu.getItems())
			{
				if (item.getText().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					if (event.type == Event::MouseButtonPressed)
					{
						menu.setItemPicked(item);

						if (event.type == Event::MouseMoved)
						{
							if (!item.getText().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
							{
								menu.setItemUnpicked(item);
							}
						}
					}

					if (event.type == Event::MouseButtonReleased)
					{
						menu.setItemUnpicked(item);
					}
				}

				if (item.isPicked() && event.type == Event::MouseButtonReleased)
				{
					menu.setItemUnpicked(item);
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

		if (console.showingConsole())
		{
			console.getTextsForChanging().at(size_t(0))
				.setString("mouseGlobal - " +
					std::to_string(Mouse::getPosition().x) + "," +
					std::to_string(Mouse::getPosition().y));

			console.getTextsForChanging().at(size_t(1))
				.setString("mouseLocal - " +
					std::to_string(Mouse::getPosition(window).x) + "," +
					std::to_string(Mouse::getPosition(window).y));


			window.draw(console.getBgShape());
			for (auto& text : console.getTexts())
			{
				window.draw(text);
			}
		}

		window.display();
	}

	return 0;
}