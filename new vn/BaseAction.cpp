#include "BaseAction.h"

BaseAction::BaseAction(){}

BaseAction::BaseAction(int orderNumber, ActionType actionType)
{
	m_orderNumber = orderNumber;
	m_actionType = actionType;
}

int BaseAction::getOrderNumber()
{
	return m_orderNumber;
}

void BaseAction::execute(sf::RenderWindow& window, sf::Clock clock)
{
	if (typeid(decltype(clock)).name() == "class BackgroundAction")
	{
		std::cout << "+" << std::endl;
	}
	else
	{
		std::cout << "-" << std::endl;
	}
}