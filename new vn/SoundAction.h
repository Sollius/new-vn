#pragma once
#include "BaseAction.h"
#include "SoundActionType.h"

class SoundAction : public BaseAction
{
private:
	int m_id = 0;
	sf::Sound m_sound = sf::Sound();
	sf::SoundBuffer m_soundBuffer = sf::SoundBuffer();
	float m_delayInSecs = 0.f;

	SoundActionType m_soundActionType = SoundActionType::NONE;

public:
	SoundAction();
	~SoundAction();

	SoundAction(int orderNumber, ActionType actionType, int id, SoundActionType soundActionType, std::string fileName);

	SoundAction(int orderNumber, ActionType actionType, int id, SoundActionType soundActionType, std::string fileName, float delayInSecs);

	int getSoundId();

	sf::Sound& getSound();

	sf::SoundBuffer& getSoundBuffer();

	SoundActionType getSoundActionType();

	void setSkipped();
};