#include "Menu.h"
#include "Game.h"
#include "Player.h"



int Menu(RenderWindow& window, DebugConsole debugConsole, bool debug, Clock clock, Player& player)
{
	Loading loading(sf::Color(100, 100, 100, 150), sf::Color(50, 50, 50, 200), sf::Color(0, 150, 0, 200));
	loading.showLoadingBarInCenter(window, Vector2f(200, 20), 4.f, clock);

	sf::Texture menuBgTexture = sf::Texture();

	if (!menuBgTexture.loadFromFile("resources\\img\\img_menu_bg.png"))
	{
		throw __uncaught_exception;
		std::cout << "Ошибка при загрузке фона меню" << std::endl;
		exit(1);
	}
	
	int cuttenPixels = 2;
	sf::Sprite menuBgSprite = sf::Sprite(menuBgTexture, IntRect(cuttenPixels, cuttenPixels, menuBgTexture.getSize().x - (cuttenPixels * 2), menuBgTexture.getSize().y - (cuttenPixels * 2)));
	float scale = (float)window.getSize().x / (float)menuBgTexture.getSize().x + 0.004;
	menuBgSprite.setScale(scale, scale);

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

	std::string menuMusicFileFullPath = "resources\\snd\\music\\snd_menu.wav";
	sf::Music menuMusic = sf::Music();

	if (!menuMusic.openFromFile(menuMusicFileFullPath))
	{
		throw __uncaught_exception;
		std::cout << "Ошибка при открытии файла музыки меню" << std::endl;
		exit(1);
	}

	menuMusic.setVolume(100.f);
	menuMusic.setLoop(true);
	menuMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(4.f), sf::seconds(112.f)));
	//// для тестирования петли
	////menuMusic.setPlayingOffset(sf::seconds(100.f));
	menuMusic.play();

	Time time = clock.restart();

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
				break;
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
				if (item.getText().getGlobalBounds().contains((float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y))
				{
					if (event.type == Event::MouseButtonPressed)
					{
						m_menuBlock.setItemPicked(item);

						if (event.type == Event::MouseMoved)
						{
							if (!item.getText().getGlobalBounds().contains((float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y))
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
							menuMusic.stop();
							Game(window, debugConsole, debug, clock, player, 1);
							menuMusic.play();
							break;
						case MenuStringFunction::LOAD_GAME:
							menuMusic.stop();
							Game(window, debugConsole, debug, clock, player, 2);
							menuMusic.play();
							break;
						case MenuStringFunction::SETTINGS:
							break;
						case MenuStringFunction::EXIT:
							menuMusic.stop();
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

		window.draw(menuBgSprite);

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