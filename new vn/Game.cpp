#include "Game.h"

#include "BackgroundAction.h"
#include "ActionExecutor.h"
#include "Scene.h"
#include "CharacterAction.h"
#include "TextAction.h"



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

	Font defaultFont = Font();
	defaultFont.loadFromFile("calibri.ttf");

	Texture bgTexture, charTexture;
	bgTexture.loadFromFile("menu_bg.jpg");
	sf::Sprite bgSprite = Sprite(bgTexture, IntRect(Vector2i(0, 0), (Vector2i)bgTexture.getSize()));

	charTexture.loadFromFile("char0.png");
	Sprite charSprite = Sprite(charTexture, IntRect(Vector2i(0, 0), (Vector2i)charTexture.getSize()));

	Vector2f charPosition = Vector2f(500, 200);

	Vector2f uiFluctuation = Vector2f(600, 40);
	Vector2f uiPosition = Vector2f(uiFluctuation.x / 2, (window.getSize().y / 4) * 3);

	Scene scene = Scene();
	scene.setBackground(bgSprite);
	scene.setUserInterface(RectangleShape(sf::Vector2f(window.getSize().x - uiFluctuation.x, (window.getSize().y / 4 - uiFluctuation.y))));
	scene.getUserInterfaceForChanging().setPosition(uiPosition);
	scene.getUserInterfaceForChanging().setFillColor(sf::Color(50, 50, 50, 255));
	scene.getUserInterfaceForChanging().setOutlineColor(sf::Color::Black);
	scene.getUserInterfaceForChanging().setOutlineThickness(4);

	//////////////////////////////////////////////////////
	///////////////// ACTIONS DEFINITION /////////////////
	//////////////////////////////////////////////////////

	scene.setActions(std::vector<std::shared_ptr<BaseAction>>
	{
		std::shared_ptr<BaseAction>(std::make_shared<BackgroundAction>(0, ActionType::BACKGROUND, BgActionType::MOVING_IN, scene.getBackground(), 3.f, nullVectorF, nullVectorF)),
		std::shared_ptr<BaseAction>(std::make_shared<CharacterAction>(1, ActionType::CHARACTER, CharActionType::MOVING_IN, charSprite, 1.f, charPosition, charPosition)),
	});
	scene.display(window, clock);

	scene.setActions(std::vector<std::shared_ptr<BaseAction>>
	{
		std::shared_ptr<BaseAction>(std::make_shared<CharacterAction>(1, ActionType::CHARACTER, CharActionType::AWAIT, charSprite, 5.f, charPosition, charPosition)),
		std::shared_ptr<BaseAction>(std::make_shared<TextAction>(0, ActionType::TEXT, 0, TextActionType::MOVING_IN, sf::Text(sf::String(L"Ты кто такой, сука?"), defaultFont, 20), scene.getUserInterface().getPosition())),
	});
	scene.display(window, clock);

	scene.setActions(std::vector<std::shared_ptr<BaseAction>>
	{
		std::shared_ptr<BaseAction>(std::make_shared<CharacterAction>(1, ActionType::CHARACTER, CharActionType::AWAIT, charSprite, 5.f, charPosition, charPosition)),
		std::shared_ptr<BaseAction>(std::make_shared<BackgroundAction>(2, ActionType::BACKGROUND, BgActionType::MOVING_THROUGH, scene.getBackground(), 3, Vector2f(0.f, 0.f), Vector2f(200.f, 0.f))),
	});
	scene.display(window, clock);

	scene.setActions(std::vector<std::shared_ptr<BaseAction>>
	{
		std::shared_ptr<BaseAction>(std::make_shared<BackgroundAction>(3, ActionType::BACKGROUND, BgActionType::MOVING_OUT, bgSprite, 5.f, Vector2f(200.f, 0.f), Vector2f(200.f, 0.f))),
		std::shared_ptr<BaseAction>(std::make_shared<CharacterAction>(3, ActionType::CHARACTER, CharActionType::MOVING_OUT, charSprite, 2.f, charPosition, charPosition)),
	});
	scene.display(window, clock);

	return 0;
}