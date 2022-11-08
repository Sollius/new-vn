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
		m_sprite.setColor(Color(255, 255, 255, 0));
		setCurrentAlpha((float)m_sprite.getColor().a);
		setColorChangingStep({0.f, 0.f, 0.f, 255 / (getDuration() * 60)});
		break;
	case BgActionType::MOVING_THROUGH:
		m_sprite.setPosition(getStartPoint());
		setMovingStep(Vector2f((getEndPoint().x - getStartPoint().x) / (getDuration() * 60), (getEndPoint().y - getStartPoint().y) / (getDuration() * 60)));
		break;
	case BgActionType::MOVING_OUT:
		m_sprite.setPosition(getStartPoint());
		m_sprite.setColor(Color(255, 255, 255, 255));
		setCurrentAlpha((float)m_sprite.getColor().a);
		setColorChangingStep({0.f, 0.f, 0.f, 255 / (getDuration() * 60)});
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
			{
				break;
			}

			case BgActionType::AWAIT:
			{
				break;
			}

			case BgActionType::MOVING_IN:
			{
				if (m_sprite.getColor().a < 255)
				{
					setCurrentAlpha(getCurrentAlpha() + std::get<3>(getColorChangingStep()));
					m_sprite.setColor(Color(255, 255, 255, getCurrentAlpha()));
				}
				else
				{
					m_sprite.setColor(Color(255, 255, 255, 255));
					setState(true);
				}
				break;
			}

			case BgActionType::MOVING_OUT:
			{
				if (m_sprite.getColor().a > 0)
				{
					setCurrentAlpha(getCurrentAlpha() - std::get<3>(getColorChangingStep()));
					m_sprite.setColor(Color(255, 255, 255, getCurrentAlpha()));
				}
				else
				{
					m_sprite.setColor(Color(255, 255, 255, 0));
					setState(true);
				}

				break;
			}

			case BgActionType::MOVING_THROUGH:
			{
				if ((getMovingStep().x > 0 && getMovingStep().x > (m_sprite.getPosition().x - getEndPoint().x)) ||
					(getMovingStep().x < 0 && getMovingStep().x < (m_sprite.getPosition().x + getEndPoint().x)))
				{
					m_sprite.setPosition(Vector2f(m_sprite.getPosition().x + getMovingStep().x, m_sprite.getPosition().y + getMovingStep().y));
				}
				else
				{
					m_sprite.setPosition(getEndPoint());
					setState(true);
				}
				break;
			}
		}
	}

	return;
}