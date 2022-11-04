#include "BaseAction.h"

BaseAction::BaseAction(){}

BaseAction::BaseAction(int orderNumber, ActionType actionType, float actionDuration, Vector2f movingStartPoint, Vector2f movingEndPoint)
{
	m_orderNumber = orderNumber;
	m_actionType = actionType;
	m_actionDurationInS = actionDuration;
	m_movingStartPoint = movingStartPoint;
	m_movingEndPoint = movingEndPoint;
}

void BaseAction::setState(bool state)
{
	m_isActionOver = state;
}

int BaseAction::getOrderNumber()
{
	return m_orderNumber;
}

float BaseAction::getDuration()
{
	return m_actionDurationInS;
}

bool BaseAction::getState()
{
	return m_isActionOver;
}

Vector2f BaseAction::getStartPoint()
{
	return m_movingStartPoint;
}

Vector2f BaseAction::getEndPoint()
{
	return m_movingEndPoint;
}

Sprite BaseAction::execute(sf::RenderWindow& window, sf::Clock clock)
{
	if (typeid(decltype(clock)).name() == "class BaseAction")
	{
		std::cout << "+" << std::endl;
	}
	else
	{
		std::cout << "-" << std::endl;
	}

	throw __uncaught_exception;
	exit(1);
}