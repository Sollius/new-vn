#pragma once

#include "MainHeader.h"

class Player
{
private:
	std::vector<std::tuple<std::string, int>>	m_flags =			std::vector<std::tuple<std::string, int>>();
	std::vector<std::tuple<std::string, int>>	m_playerSettings =	std::vector<std::tuple<std::string, int>>();
	std::string m_saveFileName = "saves\\save.me";

	std::string m_playerName = "user1";

public:
	void addFlag(std::tuple<std::string, int> flag);



	int getFlag(std::string flagId);

	std::vector<std::tuple<std::string, int>> getAllFlags();



	void writePlayerProgress();

	void readPlayerProgress();

	void rewritePlayerProgress();
};