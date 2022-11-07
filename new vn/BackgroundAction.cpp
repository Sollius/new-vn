#include "BackgroundAction.h"

BackgroundAction::BackgroundAction() {};

BackgroundAction::BackgroundAction(
	int orderNumber,
	ActionType actionType,
	BgActionType bgActionType,
	sf::Sprite sprite,
	float actionDuration,
	Vector2f movingStartPoint,
	Vector2f movingEndPoint) :
		BaseAction(orderNumber, actionType, actionDuration, movingStartPoint, movingEndPoint)
{
	m_sprite = sprite;
	m_actionType = bgActionType;

	switch (m_actionType)
	{
	case BgActionType::NONE:
		break;
	case BgActionType::AWAIT:
		break;
	case BgActionType::MOVING_IN:
		m_sprite.setPosition(getStartPoint());
		m_currentAlpha = (float)m_sprite.getColor().a;
		m_sprite.setColor(Color(255, 255, 255, 0));
		m_colorChangingStep = { 0.f, 0.f, 0.f, 255 / (getDuration() * 60) };
		break;
	case BgActionType::MOVING_THROUGH:
		m_sprite.setPosition(getStartPoint());
		m_movingStep = Vector2f((getEndPoint().x - getStartPoint().x) / (getDuration() * 60), (getEndPoint().y - getStartPoint().y) / (getDuration() * 60));
		break;
	case BgActionType::MOVING_OUT:
		m_sprite.setPosition(getStartPoint());
		m_currentAlpha = (float)m_sprite.getColor().a;
		m_sprite.setColor(Color(255, 255, 255, 255));
		m_colorChangingStep = { 0.f, 0.f, 0.f, 255 / (getDuration() * 60) };
		break;
	}
}

void BackgroundAction::setSprite(Sprite *sprite)
{
	m_sprite = *sprite;
}

sf::Sprite BackgroundAction::getSprite()
{
	return m_sprite;
}

void BackgroundAction::execute(sf::Clock clock)
{
	if (!getState())
	{
		switch (m_actionType)
		{
		case BgActionType::NONE:
			break;
		case BgActionType::AWAIT:
			break;
		case BgActionType::MOVING_IN:
			if (m_sprite.getColor().a < 255)
			{
				m_currentAlpha += std::get<3>(m_colorChangingStep);
				m_sprite.setColor(Color(255, 255, 255, m_currentAlpha));
			}
			else
			{
				m_sprite.setColor(Color(255, 255, 255, 255));
				setState(true);
			}
			break;
		case BgActionType::MOVING_THROUGH:
			if ((m_movingStep.x > 0 && m_movingStep.x > (m_sprite.getPosition().x - getEndPoint().x)) ||
				(m_movingStep.x < 0 && m_movingStep.x < (m_sprite.getPosition().x + getEndPoint().x)))
			{
				m_sprite.setPosition(Vector2f(m_sprite.getPosition().x + m_movingStep.x, m_sprite.getPosition().y + m_movingStep.y));
			}
			else
			{
				m_sprite.setPosition(getEndPoint());
				setState(true);
			}
			break;
			break;
		case BgActionType::MOVING_OUT:
			if (m_sprite.getColor().a > 0)
			{
				m_currentAlpha -= std::get<3>(m_colorChangingStep);
				m_sprite.setColor(Color(255, 255, 255, m_currentAlpha));
			}
			else
			{
				m_sprite.setColor(Color(255, 255, 255, 0));
				setState(true);
			}

			break;
		}
	}

	return;

	////if (getState())
	////{
	////	if (m_actionType == BgActionType::MOVING_IN)
	////	{
	////		m_colorChangingStep = { 0.f, 0.f, 0.f, 255 / (getDuration() * 60) };
	////	}

	////	switch (m_actionType)
	////	{
	////	case BgActionType::MOVING_IN:
	////		m_sprite.setColor(Color(255, 255, 255, 0));
	////		m_colorChangingStep = { 0.f, 0.f, 0.f, 255 / (getDuration() * 60) };
	////		break;
	////	case BgActionType::MOVING_OUT:
	////		m_sprite.setColor(Color(255, 255, 255, 255));
	////		m_colorChangingStep = { 0.f, 0.f, 0.f, 255 / (getDuration() * 60) };
	////		break;
	////	case BgActionType::MOVING_THROUGH:
	////		break;
	////	}

	////	setState(!getState());
	////}

	////Vector2f bgMovingStep = Vector2f((getEndPoint().x - getStartPoint().x) / getDuration() * 60, (getEndPoint().y - getStartPoint().y) / getDuration() * 60);


	////sf::Time time = clock.restart();

	////	////while (window.pollEvent(event))
	////	////{
	////	////	switch (event.type)
	////	////	{
	////	////	case sf::Event::Closed:
	////	////		window.close();
	////	////		break;
	////	////	case sf::Event::KeyPressed:
	////	////		switch (event.key.code)
	////	////		{
	////	////		case sf::Keyboard::Escape:
	////	////			return;
	////	////			break;
	////	////		}
	////	////	}
	////	////}

	////	switch (m_actionType)
	////	{
	////		case BgActionType::MOVING_IN:
	////		{
	////			time = clock.getElapsedTime();

	////			int a = m_sprite.getColor().a;
	////			if (time.asMicroseconds() >= 16667 && m_sprite.getColor().a < 255)
	////			{
	////				time = clock.restart();
	////				m_sprite.setColor(sf::Color(
	////					m_sprite.getColor().r,
	////					m_sprite.getColor().g,
	////					m_sprite.getColor().b,
	////					m_sprite.getColor().a + std::get<3>(m_colorChangingStep)));
	////			}
	////			else
	////				if (m_sprite.getColor().a >= 255)
	////				{
	////					setState(!getState());
	////				}

	////			break;
	////		}

	////		case BgActionType::MOVING_OUT:
	////		{
	////			time = clock.getElapsedTime();

	////			////if (time.asMicroseconds() >= 16667 && spriteColorAlpha > 0)
	////			////{
	////			////	time = clock.restart();
	////			////	spriteColorAlpha = (spriteColorAlpha - std::get<3>(m_colorChangingStep) < 0 ? 0 : spriteColorAlpha - std::get<3>(m_colorChangingStep));
	////			////	m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, spriteColorAlpha));
	////			////}
	////			////else
	////			////	if (spriteColorAlpha <= 0)
	////			////	{
	////			////		setState(true);
	////			////	}

	////			return;
	////			break;
	////		}

	////		case BgActionType::MOVING_THROUGH:
	////		{	
	////			time = clock.getElapsedTime();
	////	
	////			if (time.asMicroseconds() > 16667)
	////			{
	////				time = clock.restart();
	////				m_sprite.setPosition(m_sprite.getPosition() + bgMovingStep);
	////			}

	////			if (m_sprite.getPosition().x - getEndPoint().x > bgMovingStep.x && bgMovingStep.x > 0.f)
	////				m_sprite.setPosition(getEndPoint());

	////			if (m_sprite.getPosition().x - getEndPoint().x < bgMovingStep.x && bgMovingStep.x < 0.f)
	////				m_sprite.setPosition(getEndPoint());

	////			if (getStartPoint() == getEndPoint())
	////			{
	////				setState(true);
	////			}
	////			return;

	////			break;
	////		}
	////	}
}