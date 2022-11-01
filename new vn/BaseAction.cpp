#include "BaseAction.h"

BaseAction::BaseAction(){}

BaseAction::BaseAction(int orderNumber, ActionType actionType, float actionDuration)
{
	m_orderNumber = orderNumber;
	m_actionType = actionType;
	m_actionDurationInS = actionDuration;
}

int BaseAction::getOrderNumber()
{
	return m_orderNumber;
}

float BaseAction::getDuration()
{
	return m_actionDurationInS;
}

void BaseAction::execute(sf::RenderWindow& window, sf::Clock clock)
{
	if (typeid(decltype(clock)).name() == "class BaseAction")
	{
		std::cout << "+" << std::endl;
	}
	else
	{
		std::cout << "-" << std::endl;
	}

	throw __uncaught_exception;
	exit(1);
}