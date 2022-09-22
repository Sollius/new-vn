#pragma once
#include <vector>
#include "MenuItem.h"

class Menu
{
private:
	int						m_itemsCount	= 0;
	Vector2f				m_startPoint	= Vector2f(0.f, 0.f);
	Vector2f				m_size			= Vector2f(0.f, 0.f);
	RectangleShape			m_mainShape		= RectangleShape(Vector2f(0.f, 0.f));
	std::vector<MenuItem>	m_items			= std::vector<MenuItem>(size_t(0));
	Font					m_font			= Font();
	int						m_fontSize		= 20;
	std::string				m_alignment		= "left";
	Texture					m_texture		= Texture();
	Sprite					m_sprite		= Sprite();

public:
	Menu();

	Menu(int itemsCount, Vector2f startPoint, Vector2f size, std::vector<sf::String> strings, Color textFillColor, std::string alignment, std::string bgImageName);

	std::vector<MenuItem>& getItems();

	RectangleShape getMainShape();

	Sprite getSprite();
};

