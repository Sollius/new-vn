#include "CharacterAction.h"

CharacterAction::CharacterAction() {};

CharacterAction::CharacterAction(
	int orderNumber,
	ActionType actionType,
	CharActionType charActionType,
	sf::Sprite sprite,
	float actionDuration,
	Vector2f movingStartPoint,
	Vector2f movingEndPoint) :
		BaseAction(orderNumber, actionType, actionDuration, movingStartPoint, movingEndPoint)
{
	m_sprite = sprite;
	m_actionType = charActionType;

	switch (m_actionType)
	{
	case CharActionType::NONE:
		break;
	case CharActionType::AWAIT:
		break;
	case CharActionType::MOVING_IN:
		m_sprite.setPosition(getStartPoint());
		m_sprite.setColor(Color(255, 255, 255, 0));
		setCurrentAlpha((float)m_sprite.getColor().a);
		setColorChangingStep({0.f, 0.f, 0.f, 255 / (getDuration() * 60)});
		break;
	case CharActionType::MOVING_THROUGH:
		m_sprite.setPosition(getStartPoint());
		setMovingStep(Vector2f((getEndPoint().x - getStartPoint().x) / (getDuration() * 60), (getEndPoint().y - getStartPoint().y) / (getDuration() * 60)));
		break;
	case CharActionType::MOVING_OUT:
		m_sprite.setPosition(getStartPoint());
		setCurrentAlpha((float)m_sprite.getColor().a);
		m_sprite.setColor(Color(255, 255, 255, 255));
		setColorChangingStep({0.f, 0.f, 0.f, 255 / (getDuration() * 60)});
		break;
	}
}

Sprite CharacterAction::getSprite()
{
	return m_sprite;
}

void CharacterAction::execute(Clock clock)
{
	if (!getState())
	{
		switch (m_actionType)
		{
			case CharActionType::NONE:
			{
				break;
			}
			case CharActionType::AWAIT:
			{
				break;
			}

			case CharActionType::MOVING_IN:
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

			case CharActionType::MOVING_OUT:
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

			case CharActionType::MOVING_THROUGH:
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

			case CharActionType::SPEAKING:
			{
				break;
			}
		}
	}
}