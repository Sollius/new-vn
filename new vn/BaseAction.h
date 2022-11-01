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
	float m_actionDurationInS = 0.f;

public:
	BaseAction();

	BaseAction(int orderNumber, ActionType actionType, float actionDuration);

	int getOrderNumber();

	float getDuration();

	virtual void execute(sf::RenderWindow& window, sf::Clock clock);
};