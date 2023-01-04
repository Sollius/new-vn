#include "MainHeader.h"
#include "GameModesHeader.h"
#include "MenuBlock.h"

#include <math.h>
#include <cmath>
#include "Player.h"

using namespace sf;

int main()
{
	setlocale(LC_ALL, "Russian");

	bool debug = true;

	Font defaultFont;
	defaultFont.loadFromFile("calibri.ttf");

	Uint32 windowStyle;
	Vector2i windowSize;

	if (debug)
	{
		windowSize = Vector2i(1280, 720);
		windowStyle = Style::Default;
	}
	else
	{
		windowSize = Vector2i(1920, 1080);
		windowStyle = Style::Fullscreen;
	}

	DebugConsole debugConsole
	(
		RectangleShape(Vector2f(400.f, 400.f)),
		Vector2f(1500, 100),
		Color(0, 0, 0, 150),
		std::vector<Text>
	{
		Text(String(""), defaultFont, 20),
			Text(String(""), defaultFont, 20),
			Text(String(""), defaultFont, 20),
			Text(String(""), defaultFont, 20),
			Text(String(""), defaultFont, 20),
			Text(String(""), defaultFont, 20),
	}
	);

	Player player;

	player.readPlayerProgress();

	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "SFML App", windowStyle);
	window.setFramerateLimit(60);

	Clock clock;

	while (window.isOpen())
	{
		Menu(window, debugConsole, debug, clock, player);
		Game(window, debugConsole, debug, clock, player);
	}

	return 0;
}