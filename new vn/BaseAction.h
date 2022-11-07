#pragma once
#include "ActionType.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ActionExecutor.h"

class BaseAction : public ActionExecutor
{
private:
	int m_orderNumber = 0;
	ActionType m_actionType = ActionType::NONE;
	Vector2f m_movingStartPoint = Vector2f(0.f, 0.f);
	Vector2f m_movingEndPoint = Vector2f(0.f, 0.f);
	float m_actionDurationInS = 0.f;
	bool m_isActionOver = false;

public:
	BaseAction();

	BaseAction(int orderNumber, ActionType actionType, float actionDuration, Vector2f movingStartPoint, Vector2f movingEndPoint);

	void setState(bool state);

	int getOrderNumber();

	float getDuration();

	virtual bool getState();

	virtual Sprite getSprite();

	Vector2f getStartPoint();

	Vector2f getEndPoint();

	virtual void execute(sf::Clock clock);
};