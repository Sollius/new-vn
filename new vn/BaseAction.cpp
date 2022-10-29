#include "BaseAction.h"
#include "ActionType.h"

BaseAction::BaseAction(int orderNumber, ActionType actionType)
{
	m_orderNumber = orderNumber;
	m_actionType = actionType;
}

int BaseAction::getOrderNumber()
{
	return m_orderNumber;
}