#pragma once
#include "ActionType.h"

class BaseAction
{
private:
	int m_orderNumber = 0;
	ActionType m_actionType = ActionType::NONE;

public:
	BaseAction(int orderNumber, ActionType actionType);

	int getOrderNumber();
};

