#pragma once
#include <vector>
#include "MenuItem.h"

class MenuBlock
{
private:
	int						m_itemsCount	= 0;
	Vector2f				m_startPoint	= Vector2f(0.f, 0.f);
	Vector2f				m_size			= Vector2f(0.f, 0.f);
	RectangleShape			m_mainShape		= RectangleShape(Vector2f(0.f, 0.f));
	std::vector<MenuItem>	m_items			= std::vector<MenuItem>(size_t(0));
	Color					m_textFillColor = Color();
	Font					m_font			= Font();
	int						m_fontSize		= 20;
	std::string				m_alignment		= "left";
	Texture					m_texture		= Texture();
	Sprite					m_sprite		= Sprite();

public:
	MenuBlock();

	MenuBlock(int itemsCount, Vector2f startPoint, Vector2f size, std::vector<sf::String> strings, Color textFillColor, std::string alignment, std::string bgImageName);

	MenuBlock(int itemsCount, Vector2f startPoint, Vector2f size, std::vector<sf::String> strings, Color textFillColor, std::string alignment);

	std::vector<MenuItem>& getItems();

	RectangleShape getMainShape();

	void setItemsBoldIfHovered(Window& window);

	Sprite getSprite();

	void itemClick(Window& window);

	void setItemHovered(MenuItem menuItem);

	void setItemPicked(MenuItem menuItem);

	void setItemUnpicked(MenuItem menuItem);
};