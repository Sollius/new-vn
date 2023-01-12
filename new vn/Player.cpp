#include "Player.h"
#include <fstream>
#include <sstream>

void Player::addFlag(std::tuple<std::string, int> flag)
{
	m_flags.push_back(flag);
}

int Player::getFlag(std::string flagId)
{
	if (!m_flags.empty())
	{
		for (auto& flag : m_flags)
		{
			if (std::get<0>(flag) == flagId)
			{
				return std::get<1>(flag);
			}
			else
			{
				throw __uncaught_exception;
				std::cout << "Флага с таким ключом не существует. Проверьте инициализацию списка флагов." << std::endl;
				return 0;
			}
		}
	}

	return 0;
}

std::vector<std::tuple<std::string, int>> Player::getAllFlags()
{
	return m_flags;
}

void Player::writePlayerProgress()
{
	std::ofstream fileStream = std::ofstream(m_saveFileName, std::ios_base::out);

	if (!fileStream.is_open())
	{
		std::cout << "Ошибка при открытии потока для работы с файлами." << std::endl;
		throw __uncaught_exception;
		exit(1);
	}

	if (!m_flags.empty())
	{
		fileStream << m_playerName << std::endl;

		for (auto& flag : m_flags)
		{
			fileStream << std::get<0>(flag) + "," + char(std::get<1>(flag) + (int)'0') << std::endl;
		}
	}
}

void Player::readPlayerProgress()
{
	std::ifstream fileStream = std::ifstream(m_saveFileName, std::ios_base::in);

	if (!fileStream.is_open())
	{
		std::ofstream{ m_saveFileName } << "user1" << std::endl;
	}
	else
	{
		bool keyReading = false, valueReading = false;
		std::string key = "", stringValue = "";
		int value = 0;

		//// очистка списка флагов (если вдруг он не пуст)
		m_flags.clear();

		for (std::string line; std::getline(fileStream, line);)
		{
			if (!keyReading)
			{
				m_playerName = line;
				////std::cout << line << std::endl;
				keyReading = true;
			}
			else
			{
				for (auto& symbol : line)
				{
					if (!valueReading)
					{
						if (symbol != ',')
						{
							key += symbol;
						}
						else
						{
							valueReading = true;
						}
					}
					else
					{
						value = (int)symbol - (int)'0';
					}
				}

				////std::cout << key + "," << value << std::endl;
				m_flags.push_back({ key, value });
			}
		}
	}
}

void Player::rewritePlayerProgress()
{
	std::ifstream fileStream = std::ifstream(m_saveFileName, std::ios_base::in);
	std::ofstream{ m_saveFileName } << "user1" << std::endl;

	this->readPlayerProgress();
}
