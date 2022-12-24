#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "ActionType.h"
#include "TextActionType.h"
#include <stdlib.h>

class TextAction : public BaseAction
{
private:
	TextActionType m_textActionType = TextActionType::NONE;
	sf::Text m_text = sf::Text();

public:
	TextAction();

	~TextAction();

	TextAction(int orderNumber, ActionType actionType, float actionDuration, TextActionType textActionType, sf::Text text, Vector2f uiPosition);

	void execute(sf::Clock clock, sf::Time time);

	sf::Text getText();

	void setSkipped();
};