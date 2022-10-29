#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "BgActionType.h"

class BackgroundAction : public BaseAction
{
private:
	sf::Sprite m_sprite = sf::Sprite();
	BgActionType m_actionType = BgActionType::NONE;
public:
	BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite);

	sf::Sprite getSprite();

	void execute(RenderWindow& window, Clock clock);

	void spriteDrawing(RenderWindow& window);
};