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

MenuItem::MenuItem(int id, sf::String string, Vector2f localStartPoint, Vector2f globalMenuPosition, Vector2f size, Font &font, int fontSize, Color textFillColor, std::string alignment)
{
	m_id = id;
	m_string = string;
	m_localStartPoint = localStartPoint;
	m_textFillColor = textFillColor;
	
	m_shape = RectangleShape(size);
	m_shape.setFillColor(Color(255, 0, 0, 50));
	m_shape.setOutlineThickness(2.f);
	m_shape.setOutlineColor(Color::Green);
	m_shape.setPosition(localToGlobalPoint(localStartPoint, globalMenuPosition));

	m_text = Text(string, font, 30);
	m_text.setFillColor(m_textFillColor);
	m_text.setOutlineThickness(1.f);
	m_text.setOutlineColor(Color::Black);
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

Text& MenuItem::getTextForChanging()
{
	return m_text;
}

int MenuItem::getId()
{
	return m_id;
}

Vector2f MenuItem::localToGlobalPoint(Vector2f localPoint, Vector2f globalPosition)
{
	return localPoint + globalPosition;
}

sf::Color MenuItem::getTextFillColor()
{
	return m_text.getFillColor();
}

sf::String MenuItem::getTextFillColorString()
{
	return sf::String(
		std::to_string(m_textFillColor.r) + ", " +
		std::to_string(m_textFillColor.g) + ", " +
		std::to_string(m_textFillColor.b));
}



void MenuItem::setTextFillColor(int colorR, int colorG, int colorB)
{
	Color newColor(colorR, colorG, colorB);
	m_textFillColor = newColor;
	m_text.setFillColor(m_textFillColor);
}

void MenuItem::setTextFillColor(int colorR, int colorG, int colorB, int colorA)
{
	Color newColor(colorR, colorG, colorB, colorA);
	m_textFillColor = newColor;
	m_text.setFillColor(m_textFillColor);
}

void MenuItem::setTextFillColor(Color color)
{
	m_textFillColor = color;
	m_text.setFillColor(m_textFillColor);
}

void MenuItem::pickSwitch()
{
	m_isPicked = !m_isPicked;
}

bool MenuItem::isPicked()
{
	return m_isPicked;
}