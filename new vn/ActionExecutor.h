#pragma once

#include "MainHeader.h"

class ActionExecutor
{
public:
	ActionExecutor();

	virtual void execute(RenderWindow& window, Clock clock);
};

