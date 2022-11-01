#include "BackgroundAction.h"

BackgroundAction::BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite, float actionDuration) : BaseAction::BaseAction(orderNumber, actionType, actionDuration)
{
	m_sprite = sprite;
	m_actionType = bgActionType;
}

BackgroundAction::BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite, float actionDuration, sf::Vector2f bgMovingEndPoint) : BaseAction(orderNumber, actionType, actionDuration)
{
	m_sprite = sprite;
	m_actionType = bgActionType;
	m_bgMovingEndPoint = bgMovingEndPoint;
}

BackgroundAction::BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite, float actionDuration, Vector2f bgMovingStartPoint, Vector2f bgMovingEndPoint) : BaseAction(orderNumber, actionType, actionDuration)
{
	m_sprite = sprite;
	m_bgMovingStartPoint = bgMovingStartPoint;
	m_sprite.setPosition(m_bgMovingStartPoint);
	m_actionType = bgActionType;
	m_bgMovingEndPoint = bgMovingEndPoint;
}

BackgroundAction::BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite, float animationSpeed, float actionDuration) : BaseAction::BaseAction(orderNumber, actionType, actionDuration)
{
	m_sprite = sprite;
	m_actionType = bgActionType;
	m_animationSpeedInFPS = animationSpeed;
}

sf::Sprite BackgroundAction::getSprite()
{
	return m_sprite;
}

void BackgroundAction::execute(sf::RenderWindow& window, sf::Clock clock)
{
	if (m_isActionOver)
	{
		m_isActionOver = false;
	}

	float alphaStep = 255 / (getDuration() * 60);
	float spriteColorAlpha = 0.f;
	Vector2f bgMovingStep = Vector2f((m_bgMovingEndPoint.x - m_bgMovingStartPoint.x) / getDuration() * 60, (m_bgMovingEndPoint.y - m_bgMovingStartPoint.y) / getDuration() * 60);

	switch (m_actionType)
	{
	case BgActionType::MOVING_IN:
		spriteColorAlpha = 0.f;
		m_sprite.setColor(Color(255, 255, 255, 0));
		break;
	case BgActionType::MOVING_OUT:
		spriteColorAlpha = 255.f;
		m_sprite.setColor(Color(255, 255, 255, 255));
		break;
	case BgActionType::MOVING_THROUGH:
		break;
	}

	sf::Time time = clock.restart();

	while (!m_isActionOver)
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
			case BgActionType::MOVING_IN:
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
						m_isActionOver = true;
					}

				spriteDrawing(window);
				break;
			}

			case BgActionType::MOVING_OUT:
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
						m_isActionOver = true;
					}

				spriteDrawing(window);
				break;
			}

			case BgActionType::MOVING_THROUGH:
			{	
				time = clock.getElapsedTime();
		
				if (time.asMicroseconds() > 16667)
				{
					time = clock.restart();
					m_sprite.setPosition(m_sprite.getPosition() + bgMovingStep);
				}

				if (m_sprite.getPosition().x - m_bgMovingEndPoint.x > bgMovingStep.x && bgMovingStep.x > 0.f)
					m_sprite.setPosition(m_bgMovingEndPoint);

				if (m_sprite.getPosition().x - m_bgMovingEndPoint.x < bgMovingStep.x && bgMovingStep.x < 0.f)
					m_sprite.setPosition(m_bgMovingEndPoint);

				if (m_bgMovingStartPoint == m_bgMovingEndPoint)
				{
					m_isActionOver = true;
				}

				break;
			}
		}
	}
}

void BackgroundAction::spriteDrawing(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);

	window.draw(m_sprite);

	window.display();
}