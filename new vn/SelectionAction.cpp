#include "SelectionAction.h"

SelectionAction::SelectionAction()
{
}

SelectionAction::~SelectionAction()
{
}

SelectionAction::SelectionAction(std::vector<sf::Text> optionStrings, sf::FloatRect uiBounds)
{
	int count = 1;

	for (auto& option : optionStrings)
	{
		sf::RectangleShape optionButtonShape = sf::RectangleShape(Vector2f(option.getGlobalBounds().height + 20, option.getGlobalBounds().width + 10));

		optionButtonShape.setFillColor(sf::Color(100, 100, 100, 100));
		optionButtonShape.setOutlineColor(sf::Color(0, 0, 0, 255));
		optionButtonShape.setOutlineThickness(3);
		optionButtonShape.setPosition(
			uiBounds.left + uiBounds.width - 30 + ((1000 / optionStrings.size()) * count),
			uiBounds.top + uiBounds.height - 20);

		option.setFillColor(sf::Color::White);
		option.setOutlineColor(sf::Color::Black);
		option.setOutlineThickness(2);
		option.setPosition(optionButtonShape.getPosition().x + 10, optionButtonShape.getPosition().y + 5);

		m_options.push_back(std::make_tuple(optionButtonShape, option, count++));
	}
}

SelectionAction::SelectionAction(int orderNumber, ActionType actionType, float actionDuration, std::string selectionName, std::vector<sf::Text> optionStrings, sf::FloatRect buttonZoneBounds) : BaseAction(orderNumber, actionType, actionDuration)
{
	m_selectionName = selectionName;

	int count = 1;

	for (auto& option : optionStrings)
	{
		sf::RectangleShape optionButtonShape = sf::RectangleShape(Vector2f(option.getGlobalBounds().width + 20, option.getGlobalBounds().height + 10));

		optionButtonShape.setFillColor(sf::Color(100, 100, 100, 100));
		optionButtonShape.setOutlineColor(sf::Color(0, 0, 0, 255));
		optionButtonShape.setOutlineThickness(3);
		optionButtonShape.setPosition(////100, 100 * count);
			buttonZoneBounds.left + ((buttonZoneBounds.width / optionStrings.size()) * (count - 1)),
			////uiBounds.width - 
			buttonZoneBounds.top);
			////uiBounds.top + 
			////uiBounds.height - 20);

		option.setFillColor(sf::Color::White);
		option.setOutlineColor(sf::Color::Black);
		option.setOutlineThickness(2);

		//// TODO: сделать правильное динамическое выравнивание текста по кнопке
		option.setPosition(optionButtonShape.getPosition().x + 10, optionButtonShape.getPosition().y + 2);

		m_options.push_back(std::make_tuple(optionButtonShape, option, count++));
	}
}

std::vector<std::tuple<sf::RectangleShape, sf::Text>> SelectionAction::getButtons()
{
	std::vector<std::tuple<sf::RectangleShape, sf::Text>> buttons;

	for (auto& button : m_options)
	{
		buttons.push_back(std::tuple<sf::RectangleShape, sf::Text>{ std::get<0>(button), std::get<1>(button) });
	}

	return buttons;
}

std::string SelectionAction::getSelectionName()
{
	return m_selectionName;
}

int SelectionAction::getSelectedOptionNumber(Vector2f point)
{
	for (auto& option : m_options)
	{
		if (std::get<0>(option).getGlobalBounds().contains(point))
		{
			return std::get<2>(option);
		}
	}

	return -1;
}

void SelectionAction::execute(sf::Clock, sf::Time)
{
	if (!getState())
	{
		for(auto & option : m_options)
		{

		}
	}
}

void SelectionAction::setSkipped()
{
	setState(true);
}

void SelectionAction::setHovered(Vector2f point)
{
	for (auto& option : m_options)
	{
		if (std::get<0>(option).getGlobalBounds().contains(point))
		{
			std::get<0>(option).setFillColor(Color::Blue);
		}
		else
		{
			std::get<0>(option).setFillColor(m_buttonColor);
		}
	}
}

void SelectionAction::setUnhovered(Vector2f point)
{
	for (auto& option : m_options)
	{
		if (std::get<0>(option).getGlobalBounds().contains(point))
		{
			std::get<0>(option).setFillColor(m_buttonColor);
		}
	}
}