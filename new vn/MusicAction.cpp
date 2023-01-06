
#include "MusicAction.h"

MusicAction::MusicAction()
{
}

MusicAction::~MusicAction()
{
}

MusicAction::MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType) : BaseAction(orderNumber, actionType)
{
	m_musicActionType = musicActionType;
}

MusicAction::MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName) : BaseAction(orderNumber, actionType)
{
	m_musicActionType = musicActionType;
	m_fileName = musicFileName;
}

MusicAction::MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName, sf::Time loopBeginning, sf::Time loopEnd) : BaseAction(orderNumber, actionType)
{
	m_musicActionType = musicActionType;
}

MusicAction::MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName, sf::Time startTime, sf::Time loopBeginning, sf::Time loopEnd) : BaseAction(orderNumber, actionType)
{
	m_musicActionType = musicActionType;
}

int MusicAction::getMusicId()
{
	return m_id;
}

MusicActionType MusicAction::getMusicActionType()
{
	return m_musicActionType;
}

std::string MusicAction::getMusicFileName()
{
	return m_fileName;
}

void MusicAction::execute(sf::Clock clock, Time time)
{
	switch (m_musicActionType)
	{
		case MusicActionType::PLAY:
		{
			////m_music.play();
		}
		case MusicActionType::PAUSE:
		{
			////m_music.pause();
		}
		case MusicActionType::STOP:
		{
			////m_music.stop();
		}
		default:
		{
			throw __uncaught_exception;
			std::cout << "Ошибка при определении типа музыкального действия" << std::endl;
			exit(1);
		}
	}
}

void MusicAction::setSkipped()
{
	////switch (m_musicActionType)
	////{
	////	case CharActionType::NONE:
	////	{
	////		break;
	////	}
	////	case CharActionType::AWAIT:
	////	{
	////		break;
	////	}
	////	case CharActionType::MOVING_IN:
	////	{
	////		m_sprite.setColor(Color(255, 255, 255, 255));
	////		break;
	////	}
	////	case CharActionType::MOVING_OUT:
	////	{
	////		m_sprite.setColor(Color(255, 255, 255, 0));
	////		break;
	////	}
	////	case CharActionType::MOVING_THROUGH:
	////	{
	////		m_sprite.setPosition(getEndPosition());
	////		break;
	////	}
	////}

	setState(true);
}