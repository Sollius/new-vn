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
	m_sprite.setPosition(getStartPoint());
	m_actionType = charActionType;
}

Sprite CharacterAction::getSprite()
{
	return m_sprite;
}

Sprite CharacterAction::execute(RenderWindow& window, Clock clock)
{
	if (getState())
	{
		setState(false);
	}

	float alphaStep = 255 / (getDuration() * 60);
	float spriteColorAlpha = 0.f;
	Vector2f bgMovingStep = Vector2f((getEndPoint().x - getStartPoint().x) / getDuration() * 60, (getEndPoint().y - getStartPoint().y) / getDuration() * 60);

	switch (m_actionType)
	{
	case CharActionType::MOVING_IN:
		spriteColorAlpha = 0.f;
		m_sprite.setColor(Color(255, 255, 255, 0));
		break;
	case CharActionType::MOVING_OUT:
		spriteColorAlpha = 255.f;
		m_sprite.setColor(Color(255, 255, 255, 255));
		break;
	case CharActionType::MOVING_THROUGH:
		break;
	}

	sf::Time time = clock.restart();

	while (!getState())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					return;
					break;
				}
			}
		}

		switch (m_actionType)
		{
		case CharActionType::MOVING_IN:
		{
			time = clock.getElapsedTime();

			if (time.asMicroseconds() >= 16667 && spriteColorAlpha < 255)
			{
				time = clock.restart();
				spriteColorAlpha = (spriteColorAlpha + alphaStep > 255 ? 255 : spriteColorAlpha + alphaStep);
				m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, spriteColorAlpha));
			}
			else
				if (spriteColorAlpha >= 255)
				{
					setState(true);
				}

			spriteDrawing(window);
			break;
		}

		case CharActionType::MOVING_OUT:
		{
			time = clock.getElapsedTime();

			if (time.asMicroseconds() >= 16667 && spriteColorAlpha > 0)
			{
				time = clock.restart();
				spriteColorAlpha = (spriteColorAlpha - alphaStep < 0 ? 0 : spriteColorAlpha - alphaStep);
				m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, spriteColorAlpha));
			}
			else
				if (spriteColorAlpha <= 0)
				{
					setState(true);
				}

			spriteDrawing(window);
			break;
		}

		case CharActionType::MOVING_THROUGH:
		{
			time = clock.getElapsedTime();

			if (time.asMicroseconds() > 16667)
			{
				time = clock.restart();
				m_sprite.setPosition(m_sprite.getPosition().x + bgMovingStep.x, m_sprite.getPosition().y + bgMovingStep.y);
			}

			if (m_sprite.getPosition().x - getEndPoint().x > bgMovingStep.x && bgMovingStep.x > 0.f)
				m_sprite.setPosition(getEndPoint());

			if (m_sprite.getPosition().x - getEndPoint().x < bgMovingStep.x && bgMovingStep.x < 0.f)
				m_sprite.setPosition(getEndPoint());

			if (getStartPoint().x == getEndPoint().x && getStartPoint().y == getStartPoint().y)
			{
				setState(true);
			}

			break;
		}
		}
	}
}