#pragma once
#include "BaseAction.h"
#include "MusicActionType.h"

class MusicAction : public BaseAction
{
private:
	int m_id = 0;
	std::string m_fileName = "";
	MusicActionType m_musicActionType = MusicActionType::NONE;

	float m_startTime = 0.f, m_loopStart = 0.f, m_loopEnd = 0.f;

public:
	MusicAction();
	~MusicAction();

	MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType);

	MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName);

	MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName, float loopBeginning, float loopEnd);

	MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName, float startTime, float loopBeginning, float loopEnd);

	virtual int getMusicId();

	MusicActionType getMusicActionType();

	virtual std::string getMusicFileName();

	std::tuple<std::string, float, float, float> getMusicFileInfo();

	virtual void execute(sf::Clock clock, Time time);

	void setSkipped();
};

