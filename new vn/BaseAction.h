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

public:
	BaseAction();

	BaseAction(int orderNumber, ActionType actionType);

	int getOrderNumber();

	virtual void execute(sf::RenderWindow& window, sf::Clock clock);
};


////
////
////#pragma once
////#include "ActionType.h"
////#include "MainHeader.h"
////#include "ActionExecutor.h"
////
////class BaseAction// : public ActionExecutor
////{
////private:
////	int m_orderNumber = 0;
////	ActionType m_actionType = ActionType::NONE;
////
////public:
////	BaseAction();
////
////	BaseAction(int orderNumber, ActionType actionType);
////
////	int getOrderNumber();
////
////	virtual void execute(RenderWindow& window, BaseAction& action, Clock clock);
////};
////