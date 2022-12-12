#pragma once

#include "MainHeader.h"

class ActionExecutor
{
public:
	ActionExecutor();

	virtual void execute(Clock clock, Time time);

	virtual bool getState();

	virtual Sprite getSprite();

	virtual Text getText();
};

