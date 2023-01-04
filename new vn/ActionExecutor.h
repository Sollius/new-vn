#pragma once

#include "MainHeader.h"
#include "BgActionType.h"
#include "CharActionType.h"
#include "TextActionType.h"

class ActionExecutor
{
public:
	ActionExecutor();

	virtual void execute(Clock clock, Time time);

	virtual bool getState();

	virtual Sprite getSprite();

	virtual Text getText();

	virtual TextActionType getTextActionType();

	virtual BgActionType getBgActionType();

	virtual CharActionType getCharActionType();

	virtual std::vector<std::tuple<sf::RectangleShape, sf::Text>> getButtons();
};

