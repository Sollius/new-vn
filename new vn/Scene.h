#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "SceneState.h"

class Scene
{
private:
	SceneState m_state = SceneState::NONE;

	sf::RectangleShape m_userInterface = sf::RectangleShape();

	bool m_isShowInterface = true;
	bool m_isAutoSkip = false;

	sf::Sprite m_background = sf::Sprite();
	std::vector<sf::Sprite> m_characters = std::vector<sf::Sprite>();
	std::vector<sf::Text> m_texts = std::vector<sf::Text>();
	std::vector<std::shared_ptr<BaseAction>> m_actions = std::vector<std::shared_ptr<BaseAction>>();


public:
	Scene();
	~Scene();

	Scene(Sprite background, std::vector<Sprite> characters);

	bool isActionsOver();

	void setActions(std::vector<std::shared_ptr<BaseAction>> actions);

	void display(RenderWindow& window, Clock clock);

	void pushAction(Sprite sprite);

	void setBackground(Sprite sprite);

	void setUserInterface(sf::RectangleShape userInterface);

	Sprite getBackground();

	RectangleShape getUserInterface();

	RectangleShape& getUserInterfaceForChanging();
};

