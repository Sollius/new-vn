
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

MusicAction::MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName, float loopBeginning, float loopEnd) : BaseAction(orderNumber, actionType)
{
	m_musicActionType = musicActionType;
	m_fileName = musicFileName;
	m_loopStart = loopBeginning;
	m_loopEnd = loopEnd;
}

MusicAction::MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName, float startTime, float loopBeginning, float loopEnd) : BaseAction(orderNumber, actionType)
{
	m_musicActionType = musicActionType;
	m_fileName = musicFileName;
	m_startTime = startTime;
	m_loopStart = loopBeginning;
	m_loopEnd = loopEnd;

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

std::tuple<std::string, float, float, float> MusicAction::getMusicFileInfo()
{
	return std::make_tuple(m_fileName, m_startTime, m_loopStart, m_loopEnd);
}

void MusicAction::execute(sf::Clock clock, Time time)
{
	setState(true);

	switch (m_musicActionType)
	{
		case MusicActionType::PLAY:
		{
			////m_music.play();

			break;
		}
		case MusicActionType::PAUSE:
		{
			////m_music.pause();

			break;
		}
		case MusicActionType::STOP:
		{
			////m_music.stop();

			break;
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