#pragma once

#include "MainHeader.h"

using namespace sf;

class MenuItem
{
private:
	int m_id = 0;
	sf::String m_string = sf::String("");
	Vector2f m_localStartPoint = Vector2f(0.f, 0.f);
	Vector2f m_globalStartPoint = Vector2f(0.f, 0.f);
	RectangleShape m_shape = RectangleShape(Vector2f(0.f, 0.f));
	Text m_text = Text();
	Color m_textFillColor = Color();

public:
	MenuItem();

	MenuItem(sf::String string, RectangleShape shape);

	MenuItem(sf::String string, Vector2f size);

	MenuItem(int id, sf::String string, Vector2f localStartPoint, Vector2f globalMenuPosition, Vector2f size, Font &font, int fontSize, Color textFillColor, std::string alignment);

	RectangleShape &getShape();

	Text getText();

	Text& getTextForChanging();

	int getId();

	Vector2f localToGlobalPoint(Vector2f localPoint, Vector2f globalPosition);

	sf::Color getTextFillColor();

	sf::String getTextFillColorString();
};

