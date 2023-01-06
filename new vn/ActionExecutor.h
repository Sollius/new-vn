#pragma once

#include "MainHeader.h"
#include "BgActionType.h"
#include "CharActionType.h"
#include "TextActionType.h"
#include "MusicActionType.h"

class ActionExecutor
{
public:
	ActionExecutor();

	virtual void execute(Clock clock, Time time);

	virtual bool getState();

	virtual Sprite getSprite();

	virtual Text getText();

	virtual std::vector<std::tuple<sf::RectangleShape, sf::Text>> getButtons();

	virtual BgActionType getBgActionType();

	virtual CharActionType getCharActionType();

	virtual TextActionType getTextActionType();

	virtual MusicActionType getMusicActionType();

	virtual int getMusicId();

	virtual std::string getMusicFileName();
};

