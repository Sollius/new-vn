#pragma once

#include "MainHeader.h"
#include "MenuStringFunction.cpp"

using namespace sf;

class MenuItem
{
private:
	int					m_id				= 0;
	sf::String			m_string			= sf::String("");
	Vector2f			m_localStartPoint	= Vector2f(0.f, 0.f);
	Vector2f			m_globalStartPoint	= Vector2f(0.f, 0.f);
	RectangleShape		m_shape				= RectangleShape(Vector2f(0.f, 0.f));
	Text				m_text				= Text();
	Color				m_textFillColor		= Color();
	MenuStringFunction	m_function			= MenuStringFunction::NONE;
	bool				m_isPicked			= false;

public:
	MenuItem();

	MenuItem(sf::String string, RectangleShape shape);

	MenuItem(sf::String string, Vector2f size);

	MenuItem(int id, sf::String string, Vector2f localStartPoint, Vector2f globalMenuPosition, Vector2f size, Font &font, int fontSize, Color textFillColor, std::string alignment);

	MenuItem(int id, sf::String string, int itemFunction, Vector2f localStartPoint, Vector2f globalMenuPosition, Vector2f size, Font& font, int fontSize, Color textFillColor, std::string alignment);

	RectangleShape &getShape();

	Text getText();

	Text& getTextForChanging();

	int getId();

	MenuStringFunction getItemFunction();

	Vector2f localToGlobalPoint(Vector2f localPoint, Vector2f globalPosition);

	sf::Color getTextFillColor();

	sf::String getTextFillColorString();

	void setTextFillColor(int colorR, int colorG, int colorB);

	void setTextFillColor(int colorR, int colorG, int colorB, int colorA);

	void setTextFillColor(Color color);

	void pickSwitch();

	bool isPicked();
};