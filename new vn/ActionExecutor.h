#pragma once

#include "MainHeader.h"
#include "BgActionType.h"
#include "CharActionType.h"
#include "TextActionType.h"
#include "MusicActionType.h"
#include "SoundActionType.h"

class ActionExecutor
{
public:
	ActionExecutor();

	virtual void execute(Clock clock, Time time);

	virtual bool getState();

	virtual Sprite getSprite();

	virtual Text getText();

	virtual sf::Text getHeader();

	virtual sf::Sound& getSound();

	virtual sf::SoundBuffer& getSoundBuffer();

	virtual std::vector<std::tuple<sf::RectangleShape, sf::Text>> getButtons();

	virtual BgActionType getBgActionType();

	virtual CharActionType getCharActionType();

	virtual TextActionType getTextActionType();

	virtual MusicActionType getMusicActionType();

	virtual SoundActionType getSoundActionType();

	virtual int getMusicId();

	virtual int getSoundId();

	virtual std::string getMusicFileName();

	virtual std::tuple<std::string, float, float, float> getMusicFileInfo();
};

