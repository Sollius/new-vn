#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "ActionType.h"
#include "TextActionType.h"
#include <stdlib.h>

/// <summary>
/// Текстовое действие. Отображает реплики персонажей и прочее подобное.
/// </summary>
class TextAction : public BaseAction
{
private:
	TextActionType	m_textActionType =	TextActionType::NONE;
	sf::Text		m_header =			sf::Text("", sf::Font(), 0);			//// туда чаще всего пишется имя говорящего
	sf::Text		m_text =			sf::Text();

	sf::Font		m_font =			sf::Font();

public:
	//// Дефолтные конструкторы.
	TextAction();
	~TextAction();

	/// <summary>
	/// Главный конструктор.
	/// </summary>
	/// <param name="orderNumber">Порядковый номер действия.</param>
	/// <param name="actionType">Тип действия.</param>
	/// <param name="actionDuration">Время действия.</param>
	/// <param name="textActionType">Тип текстового действия.</param>
	/// <param name="header">Заголовок реплики. Имя говорящего.</param>
	/// <param name="text">Текстовая строка.</param>
	/// <param name="uiPosition">Позиция пользовательского интерфейса.</param>
	TextAction(int orderNumber, ActionType actionType, float actionDuration, TextActionType textActionType, sf::String header, sf::String text, Vector2f uiPosition);

	void execute(sf::Clock clock, sf::Time time);

	sf::Text getText();

	sf::Text getHeader();

	TextActionType getTextActionType();

	void setSkipped();
};