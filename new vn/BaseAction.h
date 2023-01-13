#pragma once
#include "ActionType.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ActionExecutor.h"
#include "TextActionType.h"

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

	BaseAction(int orderNumber, ActionType actionType, float actionDuration, Vector2f movingStartPoint);

	BaseAction(int orderNumber, ActionType actionType, float actionDuration);

	BaseAction(int orderNumber, ActionType actionType);

	virtual void execute(sf::Clock clock, Time time);

	virtual void setSkipped();

	virtual void setHovered(Vector2f point);

	virtual void setUnhovered(Vector2f point);

	virtual Sprite getSprite();

	virtual sf::Text getHeader();

	virtual Text getText();

	virtual sf::Sound& getSound();

	virtual sf::SoundBuffer& getSoundBuffer();

	virtual std::vector<std::tuple<sf::RectangleShape, sf::Text>> getButtons();

	virtual int getMusicId();

	virtual int getSoundId();

	virtual std::string getMusicFileName();

	virtual std::tuple<std::string, float, float, float> getMusicFileInfo();

	virtual bool getState();

	virtual int getSelectedOptionNumber(Vector2f point);

	virtual std::string getSelectionName();

	virtual TextActionType getTextActionType();

	virtual BgActionType getBgActionType();

	virtual CharActionType getCharActionType();

	virtual MusicActionType getMusicActionType();

	virtual SoundActionType getSoundActionType();

	void setState(bool state);

	void setCurrentAlpha(float currentAlpha);

	void setColorChangingStep(std::tuple<float, float, float, float> colorChangingStep);

	void setMovingStep(Vector2f movingStep);

	ActionType getActionType();

	int getOrderNumber();

	float getDuration();

	float getCurrentAlpha();

	std::tuple<float, float, float, float> getColorChangingStep();

	Vector2f getMovingStep();

	Vector2f getStartPosition();

	Vector2f getEndPosition();
};