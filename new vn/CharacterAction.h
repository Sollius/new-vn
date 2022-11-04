#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "CharActionType.h"
#include "ActionType.h"

class CharacterAction : public BaseAction
{
private:
	CharActionType m_actionType = CharActionType::NONE;
	sf::Sprite m_sprite = sf::Sprite();

public:
	CharacterAction();

	CharacterAction(int orderNumber, ActionType actionType, CharActionType bgActionType, sf::Sprite sprite, float actionDuration, Vector2f movingStartPoint, Vector2f movingEndPoint);

	Sprite getSprite();

	virtual Sprite execute(RenderWindow& window, Clock clock);

	void spriteDrawing(RenderWindow& window);
};