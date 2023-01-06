#pragma once
#include "BaseAction.h"
#include "MusicActionType.h"

class MusicAction : public BaseAction
{
private:
	int m_id = 0;
	std::string m_fileName = "";
	MusicActionType m_musicActionType = MusicActionType::NONE;

public:
	MusicAction();
	~MusicAction();

	MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType);

	MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName);

	MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName, sf::Time loopBeginning, sf::Time loopEnd);

	MusicAction(int orderNumber, ActionType actionType, MusicActionType musicActionType, std::string musicFileName, sf::Time startTime, sf::Time loopBeginning, sf::Time loopEnd);

	virtual int getMusicId();

	MusicActionType getMusicActionType();

	virtual std::string getMusicFileName();

	virtual void execute(sf::Clock clock, Time time);

	void setSkipped();
};

