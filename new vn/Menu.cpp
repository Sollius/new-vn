#include "Menu.h"
#include <iostream>

Menu::Menu() {}

Menu::Menu(int itemsCount, Vector2f startPoint, Vector2f size, std::vector<std::string> strings, std::string alignment)
{
	m_itemsCount = itemsCount;
	m_startPoint = startPoint;
	m_size = size;
	m_mainShape = RectangleShape(size);
	m_alignment = alignment;
	
	if (!m_font.loadFromFile("calibri.ttf"))
	{
		std::cout << "Error with font loading" << std::endl;
	};

	for (int count = 0; count < itemsCount; count++)
	{
		m_items.push_back(MenuItem(strings[count], Vector2f(0.f, ((size.y / itemsCount) * count)), startPoint, Vector2f(size.x, (size.y / itemsCount)), m_font, m_alignment));
	}

	m_mainShape.setFillColor(Color(255, 255, 255, 50));
	m_mainShape.setPosition(startPoint);
	m_mainShape.setOutlineThickness(5.f);
	m_mainShape.setOutlineColor(Color(0, 0, 0, 255));
}

std::vector<MenuItem>& Menu::getItems()
{
	return m_items;
}

RectangleShape Menu::getMainShape()
{
	return m_mainShape;
}
