#pragma once

#include "MainHeader.h"
#include "BaseAction.h"
#include "SceneState.h"

class Scene
{
private:
	SceneState m_state = SceneState::NONE;

	sf::Sprite m_background = sf::Sprite();
	bool m_isShowInterface = false;
	sf::Sprite m_userInterface = sf::Sprite();
	std::vector<sf::Sprite> m_characters = std::vector<sf::Sprite>();

	bool m_isAutoSkip = false;

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

	Sprite getBackground();
};

