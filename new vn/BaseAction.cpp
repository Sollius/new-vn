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

BaseAction::BaseAction(int orderNumber, ActionType actionType, float actionDuration, Vector2f movingStartPoint)
{
	m_orderNumber = orderNumber;
	m_actionType = actionType;
	m_actionDurationInS = actionDuration;
	m_movingStartPoint = movingStartPoint;
	m_movingEndPoint = movingStartPoint;
}

BaseAction::BaseAction(int orderNumber, ActionType actionType, float actionDuration)
{
	m_orderNumber = orderNumber;
	m_actionType = actionType;
	m_actionDurationInS = actionDuration;
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

Text BaseAction::getText()
{
	throw __uncaught_exception;
	exit(1);
}

Vector2f BaseAction::getStartPosition()
{
	return m_movingStartPoint;
}

Vector2f BaseAction::getEndPosition()
{
	return m_movingEndPoint;
}

void BaseAction::execute(sf::Clock clock, Time time)
{
	throw __uncaught_exception;
	exit(1);
}

void BaseAction::setSkipped()
{
	
}