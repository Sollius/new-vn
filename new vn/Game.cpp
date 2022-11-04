#include "Game.h"

#include "BackgroundAction.h"
#include "ActionExecutor.h"
#include "Scene.h"
#include "CharacterAction.h"



int Game(sf::RenderWindow& window, DebugConsole debugConsole, bool debug, Clock clock)
{
	if (!window.isOpen())
	{
		return 0;
	}

	Vector2f nullVectorF = Vector2f(0, 0);

	Loading loading(sf::Color(100, 100, 100, 150), sf::Color(50, 50, 50, 200), sf::Color(0, 150, 0, 200));
	loading.showLoadingBarInCenter(window, Vector2f(200, 20), 4.f, clock);

	BaseAction baseAction = BaseAction();

	Texture bgTexture, charTexture;
	bgTexture.loadFromFile("menu_bg.jpg");
	sf::Sprite bgSprite = Sprite(bgTexture, IntRect(Vector2i(0, 0), (Vector2i)bgTexture.getSize()));

	charTexture.loadFromFile("char0.png");
	Sprite charSprite = Sprite(charTexture, IntRect(Vector2i(500, 200), (Vector2i)charTexture.getSize()));

	Vector2f charPosition = Vector2f(500, 200);

	Scene scene = Scene();

	std::vector<std::shared_ptr<BaseAction>> actions
	{
		std::shared_ptr<BaseAction>(std::make_shared<BackgroundAction>(0, ActionType::BACKGROUND, BgActionType::MOVING_IN, bgSprite, 3.f, nullVectorF, nullVectorF)),
		std::shared_ptr<BaseAction>(std::make_shared<CharacterAction>(1, ActionType::CHARACTER, CharActionType::MOVING_IN, charSprite, 1.f, charPosition, charPosition)),
		////std::shared_ptr<BaseAction>(std::make_shared<BackgroundAction>(2, ActionType::BACKGROUND, BgActionType::MOVING_THROUGH, bgSprite, 3, Vector2f(-200.f, -200.f), Vector2f(200.f, 200.f))),
		std::shared_ptr<BaseAction>(std::make_shared<CharacterAction>(3, ActionType::CHARACTER, CharActionType::MOVING_OUT, charSprite, 2.f, charPosition, charPosition)),
		std::shared_ptr<BaseAction>(std::make_shared<BackgroundAction>(3, ActionType::BACKGROUND, BgActionType::MOVING_OUT, bgSprite, 5.f, nullVectorF, nullVectorF))
	};

	for (auto& action : actions)
	{
		ActionExecutor& actionExecutor = *action;
		scene.setBackground(actionExecutor.execute(window, clock));
	}

	return 0;
}