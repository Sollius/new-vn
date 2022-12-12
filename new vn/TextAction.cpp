#include "TextAction.h"
#include <format>

TextAction::TextAction() {}

TextAction::~TextAction() {}

TextAction::TextAction(int orderNumber, ActionType actionType, float actionDuration, TextActionType textActionType, sf::Text text, RectangleShape uiRectangle) : BaseAction(orderNumber, actionType, actionDuration)
{
	m_textActionType = textActionType;
	m_text = text;
	m_text.setPosition(Vector2f(uiRectangle.getPosition().x + 20, uiRectangle.getPosition().y + 20));
}

void TextAction::execute(sf::Clock clock, sf::Time time)
{
	if (!getState())
	{
		switch (m_textActionType)
		{
			case TextActionType::NONE:
			{
				break;
			}

			case TextActionType::AWAIT:
			{
				break;
			}

			case TextActionType::MOVING_IN:
			{
				setState(true);
				break;
			}

			case TextActionType::MOVING_OUT:
			{
				setState(true);
				break;
			}
		}
	}
}

sf::Text TextAction::getText()
{
	return m_text;
}
