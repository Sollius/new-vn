#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "ActionType.h"
#include "BgActionType.h"

class BackgroundAction : public BaseAction
{
private:
	sf::Sprite m_sprite = sf::Sprite();
	BgActionType m_actionType = BgActionType::NONE;
	float m_animationSpeedInFPS = 0.f;
	bool m_isActionOver = false;
	Vector2f m_bgMovingStartPoint = Vector2f(0.f, 0.f);
	Vector2f m_bgMovingEndPoint = Vector2f(0.f, 0.f);

public:
	BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite, float actionDuration);

	BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite, float actionDuration, Vector2f bgMovingEndPoint);

	BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite, float actionDuration, Vector2f bgMovingStartPoint, Vector2f bgMovingEndPoint);

	BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite, float animationSpeed, float actionDuration);

	sf::Sprite getSprite();

	virtual void execute(sf::RenderWindow& window, sf::Clock clock);

	void spriteDrawing(sf::RenderWindow& window);
};