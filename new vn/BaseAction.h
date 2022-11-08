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
	float m_currentAlpha = 0.f;
	float m_actionDurationInS = 0.f;
	std::tuple<float, float, float, float> m_colorChangingStep = std::tuple<float, float, float, float>{ 0.f, 0.f, 0.f, 0.f };
	Vector2f m_movingStep = Vector2f(0.f, 0.f);
	bool m_isActionOver = false;

public:
	BaseAction();

	BaseAction(int orderNumber, ActionType actionType, float actionDuration, Vector2f movingStartPoint, Vector2f movingEndPoint);

	void setState(bool state);

	void setCurrentAlpha(float currentAlpha);

	void setColorChangingStep(std::tuple<float, float, float, float> colorChangingStep);

	void setMovingStep(Vector2f movingStep);

	ActionType getActionType();

	int getOrderNumber();

	float getDuration();

	virtual bool getState();

	float getCurrentAlpha();

	std::tuple<float, float, float, float> getColorChangingStep();

	Vector2f getMovingStep();

	virtual Sprite getSprite();

	Vector2f getStartPoint();

	Vector2f getEndPoint();

	virtual void execute(sf::Clock clock);
};