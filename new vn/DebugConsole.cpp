#include "DebugConsole.h"

DebugConsole::DebugConsole()
{
}

DebugConsole::~DebugConsole()
{
}

DebugConsole::DebugConsole(sf::RectangleShape bgShape)
{
	m_backgroundShape = bgShape;
	fontDefaultInitializing();
}

DebugConsole::DebugConsole(RectangleShape bgShape, Vector2f bgShapePosition, Color bgShapeColor, std::vector<Text> texts)
{
	m_backgroundShape = bgShape;
	m_backgroundShape.setPosition(bgShapePosition);
	m_backgroundShape.setFillColor(bgShapeColor);

	fontDefaultInitializing();

	for (int count = 0; count < texts.size(); count++)
	{
		texts.at(count).setPosition(Vector2f(bgShapePosition.x + firstElementPosition.x, bgShapePosition.y + firstElementPosition.y + (20 * count)));
		addRow(texts.at(count));
	}
}

void DebugConsole::setTexts(std::vector<Text> texts)
{
	m_texts = texts;
}

RectangleShape DebugConsole::getBgShape()
{
	return m_backgroundShape;
}

std::vector<Text>& DebugConsole::getTextsForChanging()
{
	return DebugConsole::m_texts;
}

std::vector<Text> DebugConsole::getTexts()
{
	return DebugConsole::m_texts;
}

void DebugConsole::switchShowingConsole()
{
	m_isShowConsole = !m_isShowConsole;
}

void DebugConsole::fontDefaultInitializing()
{
	if(!m_font.loadFromFile("resources\\fonts\\calibri.ttf"))
	{
		throw __uncaught_exception;
		std::cout << "Ошибка при загрузке шрифта" << std::endl;
		exit(1);
	};
}

void DebugConsole::addRow(std::string row)
{
	m_texts.push_back(Text(row, m_font, 20));
}

void DebugConsole::addRow(Text row)
{
	m_texts.push_back(row);
}