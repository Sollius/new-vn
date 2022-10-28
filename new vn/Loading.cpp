#include "Loading.h"
#include <iostream>

Loading::Loading(sf::Color outShapeFillColor, sf::Color outShapeThicknessColor, sf::Color inShapeFillColor)
{
	m_outShapeFillColor = outShapeFillColor;
	m_outShapeThicknessColor = outShapeThicknessColor;
	m_inShapeFillColor = inShapeFillColor;
};

void Loading::showLoadingBarInCenter(
	sf::RenderWindow& window,
	sf::Vector2f loadingShapeSize,
	float outlineThickness,
	sf::Clock clock
)
{
	if (window.isOpen())
	{
		m_shapes[0].setSize(loadingShapeSize);
		m_shapes[1].setSize(sf::Vector2f((loadingShapeSize.x / 100) * m_progressInPercents, loadingShapeSize.y));

		sf::Vector2f shapesPositionCenter((window.getSize().x / 2) - (m_shapes[0].getGlobalBounds().width / 2),
			(window.getSize().y / 2) - (m_shapes[0].getGlobalBounds().height / 2));

		m_shapes[0].setPosition(shapesPositionCenter);
		m_shapes[1].setPosition(shapesPositionCenter);

		m_shapes[0].setFillColor(m_outShapeFillColor);
		m_shapes[1].setFillColor(m_inShapeFillColor);

		m_shapes[0].setOutlineColor(m_outShapeThicknessColor);
		m_shapes[0].setOutlineThickness(outlineThickness);
	}

	sf::Time time = clock.restart();

	while (m_progressInPercents <= m_endPointInPercents)
	{
		time = clock.getElapsedTime();

		if (time.asMilliseconds() >= m_updateRateInMs && m_progressInPercents <= m_endPointInPercents)
		{
			increaseProgressBar();
			time = clock.restart();
			m_shapes[1].setSize(sf::Vector2f((m_shapes[0].getSize().x / 100) * m_progressInPercents, m_shapes[1].getSize().y));

			window.clear(sf::Color::Black);

			for (auto& loadingShape : m_shapes)
			{
				window.draw(loadingShape);
			}

			window.display();
		}
	}
}

void Loading::showLoadingBarInCenterWithStartProgress(
	sf::RenderWindow& window,
	sf::Vector2f loadingShapeSize,
	float outlineThickness,
	sf::Clock clock,
	float startPercentsOfProgress
)
{
	try
	{
		if (startPercentsOfProgress < 0 || startPercentsOfProgress >= 100)
		{
			throw startPercentsOfProgress;
		}

		m_progressInPercents = startPercentsOfProgress;

		if (window.isOpen())
		{
			m_shapes[0].setSize(loadingShapeSize);
			m_shapes[1].setSize(sf::Vector2f((loadingShapeSize.x / 100) * m_progressInPercents, loadingShapeSize.y));

			sf::Vector2f shapesPositionCenter((window.getSize().x / 2) - (m_shapes[0].getGlobalBounds().width / 2),
				(window.getSize().y / 2) - (m_shapes[0].getGlobalBounds().height / 2));

			m_shapes[0].setPosition(shapesPositionCenter);
			m_shapes[1].setPosition(shapesPositionCenter);

			m_shapes[0].setFillColor(m_outShapeFillColor);
			m_shapes[1].setFillColor(m_inShapeFillColor);

			m_shapes[0].setOutlineColor(m_outShapeThicknessColor);
			m_shapes[0].setOutlineThickness(outlineThickness);
		}

		sf::Time time = clock.restart();

		while (m_progressInPercents <= m_endPointInPercents)
		{
			time = clock.getElapsedTime();

			if (time.asMilliseconds() >= m_updateRateInMs && m_progressInPercents <= m_endPointInPercents)
			{
				increaseProgressBar();
				time = clock.restart();
				m_shapes[1].setSize(sf::Vector2f((m_shapes[0].getSize().x / 100) * m_progressInPercents, m_shapes[1].getSize().y));

				window.clear(sf::Color::Black);

				for (auto& loadingShape : m_shapes)
				{
					window.draw(loadingShape);
				}

				window.display();
			}
		}
	}
	catch(float)
	{
		std::cerr << "Start progress percents {" << startPercentsOfProgress << "} are not valid.";
	}
}

void Loading::showLoadingBarInCenterWithEndPoint(
	sf::RenderWindow& window,
	sf::Vector2f loadingShapeSize,
	float outlineThickness,
	sf::Clock clock,
	float endPointInPercents
)
{
	try
	{
		if (endPointInPercents < 0 || endPointInPercents >= 100)
		{
			throw endPointInPercents;
		}

		m_endPointInPercents = endPointInPercents;

		if (window.isOpen())
		{
			m_shapes[0].setSize(loadingShapeSize);
			m_shapes[1].setSize(sf::Vector2f((loadingShapeSize.x / 100) * m_progressInPercents, loadingShapeSize.y));

			sf::Vector2f shapesPositionCenter((window.getSize().x / 2) - (m_shapes[0].getGlobalBounds().width / 2),
				(window.getSize().y / 2) - (m_shapes[0].getGlobalBounds().height / 2));

			m_shapes[0].setPosition(shapesPositionCenter);
			m_shapes[1].setPosition(shapesPositionCenter);

			m_shapes[0].setFillColor(m_outShapeFillColor);
			m_shapes[1].setFillColor(m_inShapeFillColor);

			m_shapes[0].setOutlineColor(m_outShapeThicknessColor);
			m_shapes[0].setOutlineThickness(outlineThickness);
		}

		sf::Time time = clock.restart();

		while (m_progressInPercents <= endPointInPercents)
		{
			time = clock.getElapsedTime();

			if (time.asMilliseconds() >= m_updateRateInMs && m_progressInPercents <= endPointInPercents)
			{
				increaseProgressBar();
				time = clock.restart();
				m_shapes[1].setSize(sf::Vector2f((m_shapes[0].getSize().x / 100) * m_progressInPercents, m_shapes[1].getSize().y));

				window.clear(sf::Color::Black);

				for (auto& loadingShape : m_shapes)
				{
					window.draw(loadingShape);
				}

				window.display();
			}
		}
	}
	catch (float)
	{
		std::cerr << "Start progress percents {" << endPointInPercents << "} are not valid.";
	}
}

void Loading::showLoadingBarInCenterWithStartProgressAndEndPoint(
	sf::RenderWindow& window,
	sf::Vector2f loadingShapeSize,
	float outlineThickness,
	sf::Clock clock,
	float startPercentsOfProgress,
	float endPointInPercents
)
{
	try
	{
		if (startPercentsOfProgress < 0 || startPercentsOfProgress >= 100)
		{
			throw startPercentsOfProgress;
		}

		if (endPointInPercents < 0 || endPointInPercents >= 100)
		{
			throw endPointInPercents;
		}

		m_progressInPercents = startPercentsOfProgress;
		m_endPointInPercents = endPointInPercents;

		if (window.isOpen())
		{
			m_shapes[0].setSize(loadingShapeSize);
			m_shapes[1].setSize(sf::Vector2f((loadingShapeSize.x / 100) * m_progressInPercents, loadingShapeSize.y));

			sf::Vector2f shapesPositionCenter((window.getSize().x / 2) - (m_shapes[0].getGlobalBounds().width / 2),
				(window.getSize().y / 2) - (m_shapes[0].getGlobalBounds().height / 2));

			m_shapes[0].setPosition(shapesPositionCenter);
			m_shapes[1].setPosition(shapesPositionCenter);

			m_shapes[0].setFillColor(m_outShapeFillColor);
			m_shapes[1].setFillColor(m_inShapeFillColor);

			m_shapes[0].setOutlineColor(m_outShapeThicknessColor);
			m_shapes[0].setOutlineThickness(outlineThickness);
		}

		sf::Time time = clock.restart();

		while (m_progressInPercents <= endPointInPercents)
		{
			time = clock.getElapsedTime();

			if (time.asMilliseconds() >= m_updateRateInMs && m_progressInPercents <= endPointInPercents)
			{
				increaseProgressBar();
				time = clock.restart();
				m_shapes[1].setSize(sf::Vector2f((m_shapes[0].getSize().x / 100) * m_progressInPercents, m_shapes[1].getSize().y));

				window.clear(sf::Color::Black);

				for (auto& loadingShape : m_shapes)
				{
					window.draw(loadingShape);
				}

				window.display();
			}
		}
	}
	catch (float)
	{
		std::cerr << "Start progress or end point percents {" << startPercentsOfProgress << ", " << endPointInPercents << "} are not valid.";
	}
}

void Loading::increaseProgressBar()
{
	m_progressInPercents += m_progressIncreasingStep;
}