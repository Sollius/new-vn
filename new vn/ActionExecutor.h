#pragma once

#include "MainHeader.h"

class ActionExecutor
{
public:
	ActionExecutor();

	virtual Sprite execute(RenderWindow& window, Clock clock);
};

