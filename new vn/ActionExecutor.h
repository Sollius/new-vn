#pragma once

#include "MainHeader.h"

class ActionExecutor
{
public:
	ActionExecutor();

	virtual void execute(Clock clock);

	virtual bool getState();

	virtual Sprite getSprite();
};

