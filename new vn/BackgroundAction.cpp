#include "BackgroundAction.h"

BackgroundAction::BackgroundAction(int orderNumber, ActionType actionType, BgActionType bgActionType, sf::Sprite sprite) : BaseAction::BaseAction(orderNumber, actionType)
{
	m_sprite = sprite;
	m_actionType = bgActionType;
}

sf::Sprite BackgroundAction::getSprite()
{
	return m_sprite;
}

void BackgroundAction::execute(sf::RenderWindow& window, sf::Clock clock)
{
	bool isActionOver = false;

	sf::Uint8 spriteColorAlpha = 0;
	switch (m_actionType)
	{
	case BgActionType::MOVING_IN:
		spriteColorAlpha = 0;
		break;
	case BgActionType::MOVING_OUT:
		spriteColorAlpha = 255;
		break;
	case BgActionType::MOVING_THROUGH:
		break;
	}
	sf::Time time = clock.restart();

	while (!isActionOver)
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
					exit(0);
					break;
				}
			}
		}

		switch (m_actionType)
		{
		case BgActionType::MOVING_IN:
			time = clock.getElapsedTime();

			if (time.asMilliseconds() >= 10 && spriteColorAlpha < 255)
			{
				time = clock.restart();
				m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, spriteColorAlpha++));
			}
			else
				if (spriteColorAlpha >= 255)
				{
					time = clock.getElapsedTime();

					if (time.asSeconds() > 4)
					{
						isActionOver = true;
					}
				}

			spriteDrawing(window);
			break;

		case BgActionType::MOVING_OUT:
			time = clock.getElapsedTime();

			if (time.asMilliseconds() >= 10 && spriteColorAlpha > 0)
			{
				time = clock.restart();
				m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, spriteColorAlpha--));
			}
			else
				if (spriteColorAlpha <= 0)
				{
					time = clock.getElapsedTime();

					if (time.asSeconds() > 4)
					{
						isActionOver = true;
					}
				}

			spriteDrawing(window);
			break;

		case BgActionType::MOVING_THROUGH:
			break;
		}
	}
}

void BackgroundAction::spriteDrawing(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);

	window.draw(m_sprite);

	window.display();
}