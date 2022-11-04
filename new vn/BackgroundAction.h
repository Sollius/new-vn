#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "ActionType.h"
#include "BgActionType.h"

class BackgroundAction : public BaseAction
{
private:
	BgActionType m_actionType = BgActionType::NONE;
	sf::Sprite m_sprite = sf::Sprite();

public:
	BackgroundAction();

	BackgroundAction(
		int orderNumber,
		ActionType actionType,
		BgActionType bgActionType,
		sf::Sprite sprite,
		float actionDuration,
		Vector2f movingStartPoint,
		Vector2f movingEndPoint
	);

	sf::Sprite getSprite();

	virtual Sprite execute(sf::RenderWindow& window, sf::Clock clock);

	void spriteDrawing(sf::RenderWindow& window);
};