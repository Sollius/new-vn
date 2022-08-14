#pragma once

#include "MainHeader.h"

using namespace sf;

class MenuItem
{
private:
	sf::String m_string = sf::String("");
	Vector2f m_localStartPoint = Vector2f(0.f, 0.f);
	Vector2f m_globalStartPoint = Vector2f(0.f, 0.f);
	RectangleShape m_shape = RectangleShape(Vector2f(0.f, 0.f));
	Text m_text = Text();

public:
	MenuItem();

	MenuItem(sf::String string, RectangleShape shape);

	MenuItem(sf::String string, Vector2f size);

	MenuItem(sf::String string, Vector2f localStartPoint, Vector2f globalMenuPosition, Vector2f size, Font &font, int fontSize, std::string alignment);

	RectangleShape &getShape();

	Text getText();

	Vector2f localToGlobalPoint(Vector2f localPoint, Vector2f globalPosition);
};

