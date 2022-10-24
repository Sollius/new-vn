#pragma once

#include <vector>

#include "MainHeader.h"

using namespace sf;

class DebugConsole
{
private:
	bool					m_isShowConsole	=		false;
	Font					m_font =				Font();
	RectangleShape			m_backgroundShape =		RectangleShape();
	Vector2f				m_bgShapePosition =		Vector2f();
	std::vector<Text>		m_texts =				std::vector<Text>(size_t(0));
	Vector2f				firstElementPosition =	Vector2f(10, 5);

public:
	DebugConsole();
	~DebugConsole();

	DebugConsole(RectangleShape bgShape);

	DebugConsole(RectangleShape bgShape, Vector2f bgShapePosition, Color bgShapeColor, std::vector<Text> texts);

	void setTexts(std::vector<Text> texts);

	RectangleShape getBgShape();

	std::vector<Text>& getTextsForChanging();

	std::vector<Text> getTexts();

	bool showingConsole()
	{
		return m_isShowConsole;
	}

	void switchShowingConsole();

	void fontDefaultInitializing();

	void addRow(std::string row);

	void addRow(Text row);
};

