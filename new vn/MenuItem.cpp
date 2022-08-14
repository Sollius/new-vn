#include "MenuItem.h"
#include "SFML/Graphics.hpp"

using namespace sf;

MenuItem::MenuItem() {};

MenuItem::MenuItem(sf::String string, RectangleShape shape)
{
	m_string = string;
	m_shape = shape;
}

MenuItem::MenuItem(sf::String string, Vector2f size)
{
	m_string = string;
	m_shape = RectangleShape(size);
}

MenuItem::MenuItem(sf::String string, Vector2f localStartPoint, Vector2f globalMenuPosition, Vector2f size, Font &font, int fontSize, std::string alignment)
{
	m_string = string;
	m_localStartPoint = localStartPoint;
	
	m_shape = RectangleShape(size);
	m_shape.setFillColor(Color(255, 0, 0, 50));
	m_shape.setOutlineThickness(2.f);
	m_shape.setOutlineColor(Color::Green);
	m_shape.setPosition(localToGlobalPoint(localStartPoint, globalMenuPosition));

	m_text.setFillColor(Color::White);
	m_text.setOutlineThickness(1.f);
	m_text.setOutlineColor(Color::Black);
	m_text = Text(string, font, 30);
	if (alignment == "center")
	{
		m_text.setPosition(localToGlobalPoint(
			Vector2f(
				m_localStartPoint.x + ((m_shape.getGlobalBounds().width - m_text.getGlobalBounds().width) / 2),
				m_localStartPoint.y + ((m_shape.getGlobalBounds().height - m_text.getGlobalBounds().height) / 2)),
			globalMenuPosition));
	}
	else
		if (alignment == "left")
		{
			m_text.setPosition(localToGlobalPoint(
				Vector2f(
					m_localStartPoint.x,
					m_localStartPoint.y + ((m_shape.getGlobalBounds().height - m_text.getGlobalBounds().height) / 2)),
				globalMenuPosition));
		}
		else
			if (alignment == "right")
			{
				m_text.setPosition(localToGlobalPoint(
					Vector2f(
						m_localStartPoint.x + m_shape.getGlobalBounds().width - m_text.getGlobalBounds().width,
						m_localStartPoint.y + ((m_shape.getGlobalBounds().height - m_text.getGlobalBounds().height) / 2)),
					globalMenuPosition));
			}
}

RectangleShape& MenuItem::getShape()
{
	return m_shape;
}

Text MenuItem::getText()
{
	return m_text;
}

Vector2f MenuItem::localToGlobalPoint(Vector2f localPoint, Vector2f globalPosition)
{
	return localPoint + globalPosition;
}
