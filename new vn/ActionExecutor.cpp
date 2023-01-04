#include "ActionExecutor.h"
#include "TextActionType.h"

ActionExecutor::ActionExecutor() {}

void ActionExecutor::execute(Clock clock, Time time)
{
	throw __uncaught_exception;
	exit(1);
}

bool ActionExecutor::getState()
{
	throw __uncaught_exception;
	exit(1);
}

Sprite ActionExecutor::getSprite()
{
	throw __uncaught_exception;
	exit(1);
}

Text ActionExecutor::getText()
{
	throw __uncaught_exception;
	exit(1);
}

TextActionType ActionExecutor::getTextActionType()
{
	throw __uncaught_exception;
	exit(1);
}

BgActionType ActionExecutor::getBgActionType()
{
	throw __uncaught_exception;
	exit(1);
}

CharActionType ActionExecutor::getCharActionType()
{
	throw __uncaught_exception;
	exit(1);
}

std::vector<std::tuple<sf::RectangleShape, sf::Text>> ActionExecutor::getButtons()
{
	throw __uncaught_exception;
	exit(1);
}
