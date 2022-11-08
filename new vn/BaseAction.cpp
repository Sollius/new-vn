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

void BaseAction::setCurrentAlpha(float currentAlpha)
{
	m_currentAlpha = currentAlpha;
}

void BaseAction::setColorChangingStep(std::tuple<float, float, float, float> colorChangingStep)
{
	m_colorChangingStep = colorChangingStep;
}

void BaseAction::setMovingStep(Vector2f movingStep)
{
	m_movingStep = movingStep;
}

ActionType BaseAction::getActionType()
{
	return m_actionType;
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

float BaseAction::getCurrentAlpha()
{
	return m_currentAlpha;
}

std::tuple<float, float, float, float> BaseAction::getColorChangingStep()
{
	return m_colorChangingStep;
}

Vector2f BaseAction::getMovingStep()
{
	return m_movingStep;
}

Sprite BaseAction::getSprite()
{
	throw __uncaught_exception;
	exit(1);
}

Vector2f BaseAction::getStartPoint()
{
	return m_movingStartPoint;
}

Vector2f BaseAction::getEndPoint()
{
	return m_movingEndPoint;
}

void BaseAction::execute(sf::Clock clock)
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