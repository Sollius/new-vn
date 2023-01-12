#include "ActionExecutor.h"
#include "TextActionType.h"

ActionExecutor::ActionExecutor() {}

void ActionExecutor::execute(Clock clock, Time time)
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате исполнения действия\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

bool ActionExecutor::getState()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате состояния анимации\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

Sprite ActionExecutor::getSprite()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате спрайта\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

Text ActionExecutor::getText()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате текста\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

sf::Sound& ActionExecutor::getSound()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате звука\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

sf::SoundBuffer& ActionExecutor::getSoundBuffer()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате буфера звука\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

TextActionType ActionExecutor::getTextActionType()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате типа действия с текстом\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

BgActionType ActionExecutor::getBgActionType()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате типа действия с фоном\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

CharActionType ActionExecutor::getCharActionType()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате типа действия с персонажем\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

MusicActionType ActionExecutor::getMusicActionType()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате типа музыкального действия\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

SoundActionType ActionExecutor::getSoundActionType()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате типа звукового действия\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

int ActionExecutor::getMusicId()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате идентификатора музыкального файла\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

int ActionExecutor::getSoundId()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате идентификатора звука\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

std::string ActionExecutor::getMusicFileName()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате имени музыкального файла\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

std::tuple<std::string, float, float, float> ActionExecutor::getMusicFileInfo()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате информации о музыкальном файле\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}

std::vector<std::tuple<sf::RectangleShape, sf::Text>> ActionExecutor::getButtons()
{
	throw __uncaught_exception;
	std::cout << "Ошибка при возврате кнопок\nОшибка наследования виртуальной функции (ActionExecutor)" << std::endl;
	exit(1);
}
