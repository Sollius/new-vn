#include "MenuBlock.h"
#include <iostream>

MenuBlock::MenuBlock() {}

MenuBlock::MenuBlock(int itemsCount, Vector2f startPoint, Vector2f size, std::vector<sf::String> strings, Color textFillColor, std::string alignment, std::string bgImageName)
{
	m_itemsCount = itemsCount;
	m_startPoint = startPoint;
	m_size = size;
	m_mainShape = RectangleShape(size);
	m_alignment = alignment;
	m_texture.loadFromFile(bgImageName);
	m_sprite.setTexture(m_texture);
	m_textFillColor = textFillColor;
	
	if (!m_font.loadFromFile("calibri.ttf"))
	{
		std::cout << "Error with font loading" << std::endl;
	};

	for (int count = 0; count < itemsCount; count++)
	{
		m_items.push_back(MenuItem(count, strings[count], Vector2f(0.f, ((size.y / itemsCount) * count)), startPoint, Vector2f(size.x, (size.y / itemsCount)), m_font, m_fontSize, m_textFillColor, m_alignment));
	}

	m_mainShape.setFillColor(Color(255, 255, 255, 50));
	m_mainShape.setPosition(startPoint);
	m_mainShape.setOutlineThickness(5.f);
	m_mainShape.setOutlineColor(Color(0, 0, 0, 255));
}

MenuBlock::MenuBlock(int itemsCount, Vector2f startPoint, Vector2f size, std::vector<sf::String> strings, Color textFillColor, std::string alignment)
{
	m_itemsCount = itemsCount;
	m_startPoint = startPoint;
	m_size = size;
	m_mainShape = RectangleShape(size);
	m_alignment = alignment;
	m_texture.loadFromFile("menu_bg.jpg");
	m_sprite.setTexture(m_texture);
	m_textFillColor = textFillColor;

	if (!m_font.loadFromFile("calibri.ttf"))
	{
		std::cout << "Error with font loading" << std::endl;
	};

	for (int count = 0; count < itemsCount; count++)
	{
		m_items.push_back
		(
			MenuItem
			(
				count,
				strings[count],
				Vector2f(0.f, ((size.y / itemsCount) * count)),
				startPoint,
				Vector2f(size.x, (size.y / itemsCount)),
				m_font,
				m_fontSize,
				m_textFillColor,
				m_alignment
			)
		);
	}

	m_mainShape.setFillColor(Color(255, 255, 255, 50));
	m_mainShape.setPosition(startPoint);
	m_mainShape.setOutlineThickness(5.f);
	m_mainShape.setOutlineColor(Color(0, 0, 0, 255));
}

MenuBlock::MenuBlock(
	int itemsCount,
	Vector2f startPoint,
	Vector2f size,
	std::vector<std::tuple<sf::String, int>> stringsAndFunctionNumbers,
	Color textFillColor,
	std::string alignment
)
{
	m_itemsCount = itemsCount;
	m_startPoint = startPoint;
	m_size = size;
	m_mainShape = RectangleShape(size);
	m_alignment = alignment;
	m_texture.loadFromFile("menu_bg.jpg");
	m_sprite.setTexture(m_texture);
	m_textFillColor = textFillColor;

	if (!m_font.loadFromFile("calibri.ttf"))
	{
		std::cout << "Error with font loading" << std::endl;
	};

	for (int count = 0; count < itemsCount; count++)
	{
		m_items.push_back
		(
			MenuItem
			(
				count,
				std::get<0>(stringsAndFunctionNumbers[count]),
				std::get<1>(stringsAndFunctionNumbers[count]),
				Vector2f(0.f, ((size.y / itemsCount) * count)),
				startPoint,
				Vector2f(size.x, (size.y / itemsCount)),
				m_font,
				m_fontSize,
				m_textFillColor,
				m_alignment
			)
		);
	}

	m_mainShape.setFillColor(Color(255, 255, 255, 50));
	m_mainShape.setPosition(startPoint);
	m_mainShape.setOutlineThickness(5.f);
	m_mainShape.setOutlineColor(Color(0, 0, 0, 255));
}

std::vector<MenuItem>& MenuBlock::getItems()
{
	return m_items;
}

RectangleShape MenuBlock::getMainShape()
{
	return m_mainShape;
}

void MenuBlock::setItemsBoldIfHovered(Window& window)
{
	for (auto& item : m_items)
	{
		if (item.getText().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			item.getTextForChanging().setStyle(Text::Style::Bold);
		}
		else
		{
			item.getTextForChanging().setStyle(Text::Style::Regular);
		}
	}
}

Sprite MenuBlock::getSprite()
{
	return m_sprite;
}

void MenuBlock::itemClick(Window& window)
{
	for (auto& item : m_items)
	{
		if (item.getText().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
		{
			item.getTextForChanging().setFillColor(Color::White);
		}
	}
}

void MenuBlock::setItemHovered(MenuItem menuItem)
{
	for (auto& item : m_items)
	{
		if (item.getId() == menuItem.getId())
		{
			item.getTextForChanging().setStyle(Text::Style::Bold);
		}
		else
		{
			item.getTextForChanging().setStyle(Text::Style::Regular);
		}
	}
}

void MenuBlock::setItemPicked(MenuItem menuItem)
{
	for (auto& item : m_items)
	{
		if (item.getId() == menuItem.getId())
		{
			item.getTextForChanging().setFillColor(Color::White);
			item.pickSwitch();
		}
		else
		{
			item.getTextForChanging().setFillColor(m_textFillColor);
		}
	}
}

void MenuBlock::setItemUnpicked(MenuItem menuItem)
{
	for (auto& item : m_items)
	{
		if (item.getId() == menuItem.getId())
		{
			item.getTextForChanging().setFillColor(m_textFillColor);
			item.pickSwitch();
		}
		else
		{
			item.getTextForChanging().setStyle(Text::Style::Regular);
		}
	}
}
