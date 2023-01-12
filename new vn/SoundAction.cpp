#include "SoundAction.h"

SoundAction::SoundAction()
{
}

SoundAction::~SoundAction()
{
}

SoundAction::SoundAction(int orderNumber, ActionType actionType, int id, SoundActionType soundActionType, std::string fileName) : BaseAction(orderNumber, actionType)
{
	m_soundActionType = soundActionType;
	m_id = id;

	////sf::SoundBuffer buffer;
	if (!m_soundBuffer.loadFromFile("resources\\snd\\" + fileName))
	{
		throw __uncaught_exception;
		std::cout << "Ошибка при загрузке звукового файла" << std::endl;
		exit(1);
	}

	m_sound.setBuffer(m_soundBuffer);
}

SoundAction::SoundAction(int orderNumber, ActionType actionType, int id, SoundActionType soundActionType, std::string fileName, float delayInSecs) : BaseAction(orderNumber, actionType)
{
	m_soundActionType = soundActionType;
	m_id = id;

	////sf::SoundBuffer buffer;
	if (!m_soundBuffer.loadFromFile("resources\\snd\\" + fileName))
	{
		throw __uncaught_exception;
		std::cout << "Ошибка при загрузке звукового файла" << std::endl;
		exit(1);
	}

	m_sound.setBuffer(m_soundBuffer);
	m_delayInSecs = delayInSecs;
}

int SoundAction::getSoundId()
{
	return m_id;
}

sf::Sound& SoundAction::getSound()
{
	return m_sound;
}

sf::SoundBuffer& SoundAction::getSoundBuffer()
{
	return m_soundBuffer;
}

SoundActionType SoundAction::getSoundActionType()
{
	return m_soundActionType;
}

void SoundAction::setSkipped()
{
	setState(true);
}
