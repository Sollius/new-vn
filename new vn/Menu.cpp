#include "Menu.h"
#include "Game.h"



int Menu(RenderWindow& window, DebugConsole debugConsole, bool debug, Clock clock)
{
	Loading loading(sf::Color(100, 100, 100, 150), sf::Color(50, 50, 50, 200), sf::Color(0, 150, 0, 200));
	loading.showLoadingBarInCenter(window, Vector2f(200, 20), 4.f, clock);

	MenuBlock m_menuBlock = MenuBlock
	(
		4,
		Vector2f(100.f, 100.f),
		Vector2f(150.f, 250.f),
		std::vector<std::tuple<String, int>> 
		{
			std::make_tuple(String(L"New game"), 1),
			std::make_tuple(String(L"Load game"), 2),
			std::make_tuple(String(L"Settings"), 3),
			std::make_tuple(String(L"Exit"), 4)
		},
		Color(255, 255, 255, 200),
		"left"
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
					debugConsole.switchShowingConsole();
					break;
				}
			case Event::MouseMoved:
				m_menuBlock.setItemsBoldIfHovered(window);

				for (auto& menuItem : m_menuBlock.getItems())
				{
					menuItem.getShape().setFillColor(Color(255, 100, 100, 200));

					if (debugConsole.showingConsole())
					{
						debugConsole.getTextsForChanging().at(2 + menuItem.getId()).setString(
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

			for (auto& item : m_menuBlock.getItems())
			{
				if (item.getText().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					if (event.type == Event::MouseButtonPressed)
					{
						m_menuBlock.setItemPicked(item);

						if (event.type == Event::MouseMoved)
						{
							if (!item.getText().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
							{
								m_menuBlock.setItemUnpicked(item);
							}
						}
					}

					if (event.type == Event::MouseButtonReleased)
					{
						m_menuBlock.setItemUnpicked(item);

						switch (item.getItemFunction())
						{
						case MenuStringFunction::NONE:
							std::cout << "Function is not define! See the function definition." << std::endl;
							window.close();
							break;
						case MenuStringFunction::NEW_GAME:
							Game(window, debugConsole, debug, clock);
							break;
						case MenuStringFunction::LOAD_GAME:
							break;
						case MenuStringFunction::SETTINGS:
							break;
						case MenuStringFunction::EXIT:
							window.close();
							break;
						}
					}
				}

				if (item.isPicked() && event.type == Event::MouseButtonReleased)
				{
					m_menuBlock.setItemUnpicked(item);
				}
			}
		}

		window.clear(Color::Blue);

		window.draw(m_menuBlock.getSprite());

		for (auto& menuItem : m_menuBlock.getItems())
		{
			if (debug)
			{
				window.draw(menuItem.getShape());
				window.draw(m_menuBlock.getMainShape());
			}
			window.draw(menuItem.getText());
		}

		if (debugConsole.showingConsole())
		{
			debugConsole.getTextsForChanging().at(size_t(0))
				.setString("mouseGlobal - " +
					std::to_string(Mouse::getPosition().x) + "," +
					std::to_string(Mouse::getPosition().y));

			debugConsole.getTextsForChanging().at(size_t(1))
				.setString("mouseLocal - " +
					std::to_string(Mouse::getPosition(window).x) + "," +
					std::to_string(Mouse::getPosition(window).y));


			window.draw(debugConsole.getBgShape());
			for (auto& text : debugConsole.getTexts())
			{
				window.draw(text);
			}
		}

		window.display();
	}

	return 0;
}