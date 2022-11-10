#include "CharacterAction.h"

CharacterAction::CharacterAction() {};

CharacterAction::CharacterAction(
	int orderNumber,
	ActionType actionType,
	CharActionType charActionType,
	sf::Sprite sprite,
	float actionDuration,
	Vector2f startPosition,
	Vector2f endPosition) :
		BaseAction(orderNumber, actionType, actionDuration, startPosition, endPosition)
{
	m_sprite = sprite;
	m_actionType = charActionType;

	switch (m_actionType)
	{
	case CharActionType::NONE:
		break;
	case CharActionType::AWAIT:
		m_sprite.setPosition(startPosition);
		break;
	case CharActionType::MOVING_IN:
		m_sprite.setPosition(getStartPosition());
		m_sprite.setColor(Color(255, 255, 255, 0));
		setCurrentAlpha((float)m_sprite.getColor().a);
		setColorChangingStep({0.f, 0.f, 0.f, 255 / (getDuration() * 60)});
		break;
	case CharActionType::MOVING_THROUGH:
		m_sprite.setPosition(getStartPosition());
		setMovingStep(Vector2f((getEndPosition().x - getStartPosition().x) / (getDuration() * 60), (getEndPosition().y - getStartPosition().y) / (getDuration() * 60)));
		break;
	case CharActionType::MOVING_OUT:
		m_sprite.setPosition(getStartPosition());
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

void CharacterAction::execute(Clock clock, Time time)
{
	if (!getState())
	{
		time = clock.getElapsedTime();

		switch (m_actionType)
		{
			case CharActionType::NONE:
			{
				break;
			}
			case CharActionType::AWAIT:
			{
				if (time.asSeconds() < getDuration())
				{

				}
				else
				{
					setState(true);
				}

				break;
			}

			case CharActionType::MOVING_IN:
			{
				if (m_sprite.getColor().a < 255 && time.asSeconds() < getDuration())
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
				if (m_sprite.getColor().a > 0 && time.asSeconds() < getDuration())
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
				if (((getMovingStep().x > 0 && getMovingStep().x > (m_sprite.getPosition().x - getEndPosition().x)) ||
					(getMovingStep().x < 0 && getMovingStep().x < (m_sprite.getPosition().x + getEndPosition().x))) &&
					time.asSeconds() < getDuration())
				{
					m_sprite.setPosition(Vector2f(m_sprite.getPosition().x + getMovingStep().x, m_sprite.getPosition().y + getMovingStep().y));
				}
				else
				{
					m_sprite.setPosition(getEndPosition());
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