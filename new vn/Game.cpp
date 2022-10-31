#include "Game.h"

#include "BackgroundAction.h"
#include "ActionExecutor.h"



int Game(sf::RenderWindow& window, DebugConsole debugConsole, bool debug, Clock clock)
{
	if (!window.isOpen())
	{
		return 0;
	}

	Loading loading(sf::Color(100, 100, 100, 150), sf::Color(50, 50, 50, 200), sf::Color(0, 150, 0, 200));
	loading.showLoadingBarInCenter(window, Vector2f(200, 20), 4.f, clock);

	BaseAction baseAction = BaseAction();

	Texture texture;
	texture.loadFromFile("menu_bg.jpg");
	sf::Sprite sprite = Sprite(texture, IntRect(Vector2i(0, 0), Vector2i(1920, 1080)));
	BackgroundAction actions[2] =
	{
		BackgroundAction(0, ActionType::BACKGROUND, BgActionType::MOVING_IN, sprite),
		BackgroundAction(1, ActionType::BACKGROUND, BgActionType::MOVING_OUT, sprite)
	};

	for (auto& action : actions)
	{
		ActionExecutor& actionExecutor = action;
		actionExecutor.execute(window, clock);
	}

	return 0;
}