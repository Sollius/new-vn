#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "ActionType.h"
#include "TextActionType.h"
#include <stdlib.h>

/// <summary>
/// ��������� ��������. ���������� ������� ���������� � ������ ��������.
/// </summary>
class TextAction : public BaseAction
{
private:
	TextActionType	m_textActionType =	TextActionType::NONE;
	sf::Text		m_header =			sf::Text("", sf::Font(), 0);			//// ���� ���� ����� ������� ��� ����������
	sf::Text		m_text =			sf::Text();

	sf::Font		m_font =			sf::Font();

public:
	//// ��������� ������������.
	TextAction();
	~TextAction();

	/// <summary>
	/// ������� �����������.
	/// </summary>
	/// <param name="orderNumber">���������� ����� ��������.</param>
	/// <param name="actionType">��� ��������.</param>
	/// <param name="actionDuration">����� ��������.</param>
	/// <param name="textActionType">��� ���������� ��������.</param>
	/// <param name="header">��������� �������. ��� ����������.</param>
	/// <param name="text">��������� ������.</param>
	/// <param name="uiPosition">������� ����������������� ����������.</param>
	TextAction(int orderNumber, ActionType actionType, float actionDuration, TextActionType textActionType, sf::String header, sf::String text, Vector2f uiPosition);

	void execute(sf::Clock clock, sf::Time time);

	sf::Text getText();

	sf::Text getHeader();

	TextActionType getTextActionType();

	void setSkipped();
};