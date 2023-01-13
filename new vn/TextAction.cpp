#include "TextAction.h"
#include <format>

TextAction::TextAction() {}

TextAction::~TextAction() {}

TextAction::TextAction(int orderNumber, ActionType actionType, float actionDuration, TextActionType textActionType, sf::String header, sf::String text, Vector2f uiPosition) : BaseAction(orderNumber, actionType, actionDuration)
{
	if (!m_font.loadFromFile("resources\\fonts\\calibri.ttf"))
	{
		throw __uncaught_exception;
		std::cout << "Ошибка при загрузке шрифта" << std::endl;
		exit(1);
	}

	m_textActionType = textActionType;

	m_header = sf::Text(header, m_font, 30);
	m_header.setStyle(sf::Text::Style::Bold);
	m_header.setOutlineColor(sf::Color::Black);
	m_header.setOutlineThickness(2.f);
	m_header.setPosition(uiPosition.x + 20, uiPosition.y);

	m_text = sf::Text(text, m_font, 20);
	m_text.setOutlineThickness(0.5f);
	m_text.setOutlineColor(sf::Color(100, 100, 100, 255));
	m_text.setPosition(Vector2f(uiPosition.x + 20, uiPosition.y + 50));
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

sf::Text TextAction::getHeader()
{
	return m_header;
}

TextActionType TextAction::getTextActionType()
{
	return m_textActionType;
}

void TextAction::setSkipped()
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
			break;
		}
		case TextActionType::MOVING_OUT:
		{
			break;
		}
	}

	setState(true);
}