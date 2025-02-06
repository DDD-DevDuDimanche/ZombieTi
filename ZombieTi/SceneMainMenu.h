#pragma once
#ifndef SCENE_MAIN_MENU_H
#define SCENE_MAIN_MENU_H

#include "SceneGame.h"

class SceneMainMenu : public Scene
{
public:
	SceneMainMenu(sf::RenderWindow* _window, std::stack<Scene*>* scenes);
	~SceneMainMenu();

	void update(float& dt);
	void render(sf::RenderTarget* target);
};

#endif SCENE_MAIN_MENU_H