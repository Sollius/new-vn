#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "SceneState.h"

class Scene
{
private:
	SceneState m_state = SceneState::NONE;

	sf::RectangleShape m_userInterface = sf::RectangleShape();

	bool m_isShowInterface = false;
	bool m_isAutoSkip = false;

	sf::Sprite m_background = sf::Sprite();
	std::vector<sf::RectangleShape> m_buttons = std::vector<sf::RectangleShape>();
	std::vector<sf::Sprite> m_characters = std::vector<sf::Sprite>();
	std::vector<sf::Text> m_texts = std::vector<sf::Text>();

	std::vector<std::tuple<int, sf::Music&>> m_musics = std::vector<std::tuple<int, sf::Music&>>();
	sf::Music m_music = sf::Music();

	std::vector<std::shared_ptr<BaseAction>> m_actions = std::vector<std::shared_ptr<BaseAction>>();

	Player m_player = Player();

	bool m_isNeedToPlayMusic = false;


public:
	Scene();
	~Scene();

	Scene(Player& player);

	Scene(Sprite background, std::vector<Sprite> characters);

	bool isActionsOver();

	void setPlayer(Player& player);

	void setActions(std::vector<std::shared_ptr<BaseAction>> actions);

	/// <summary>
	/// Главный метод по отображению событий игры.
	/// </summary>
	/// <param name="window">Объект окна.</param>
	/// <param name="clock">Объект часов.</param>
	/// <returns></returns>
	Player display(RenderWindow& window, Clock clock);

	void pushAction(Sprite sprite);

	void setBackground(Sprite sprite);

	void setUserInterface(sf::RectangleShape userInterface);

	Sprite getBackground();

	RectangleShape getUserInterface();

	RectangleShape& getUserInterfaceForChanging();

	Player& getPlayer();

	void setMusics(std::vector<std::string> musicsFileNames);

	std::vector<std::tuple<int, sf::Music&>> getMusics();

	void addMusic(int id, std::string musicFileName, float startTime);

	void addMusicFile(std::string musicFileName);

	void addMusicFileByInfo(std::tuple<std::string, float, float, float> musicFileInfo);
};

