#include "Game.h"

#include "MainHeader.h"
#include "BackgroundAction.h"



int Game(sf::RenderWindow& window, DebugConsole debugConsole, bool debug, Clock clock)
{
	if (!window.isOpen())
	{
		return 0;
	}

	Loading loading(sf::Color(100, 100, 100, 150), sf::Color(50, 50, 50, 200), sf::Color(0, 150, 0, 200));
	loading.showLoadingBarInCenter(window, Vector2f(200, 20), 4.f, clock);

	Texture texture;
	texture.loadFromFile("menu_bg.jpg");
	BackgroundAction action0(0, ActionType::BACKGROUND, BgActionType::MOVING_IN, Sprite(texture, IntRect(Vector2i(0, 0), Vector2i(1920, 1080))));
	BackgroundAction action1(1, ActionType::BACKGROUND, BgActionType::MOVING_OUT, action0.getSprite());

	action0.execute(window, clock);
	action1.execute(window, clock);

	return 0;
}