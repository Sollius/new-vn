#pragma once

#include "BaseAction.h"

class SelectionAction : public BaseAction
{
private:
	std::vector<std::tuple<sf::RectangleShape, sf::Text, int>> m_options = std::vector<std::tuple<sf::RectangleShape, sf::Text, int>>();
	std::string m_selectionName = std::string();

	sf::Color m_buttonColor = sf::Color(100, 100, 100, 100);

public:
	SelectionAction();

	~SelectionAction();

	SelectionAction(std::vector<sf::Text> optionStrings, sf::FloatRect uiBounds);

	SelectionAction(int orderNumber, ActionType actionType, float actionDuration, std::string selectionName, std::vector<sf::Text> optionStrings, sf::FloatRect buttonZoneBounds);

	std::vector<std::tuple<sf::RectangleShape, sf::Text>> getButtons();

	std::string getSelectionName();

	int getSelectedOptionNumber(Vector2f point);

	void execute(sf::Clock, sf::Time);

	void setSkipped();

	void setHovered(Vector2f point);

	void setUnhovered(Vector2f point);
};