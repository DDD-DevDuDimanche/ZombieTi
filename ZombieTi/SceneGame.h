#pragma once
#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "Scene.h"
#include "Player.h"
#include "InterfaceHUD.h"
#include "InterfaceShop.h"
#include "InterfaceBox.h"
#include "InterfaceDeath.h"

class SceneGame : public Scene
{
public:
	SceneGame(sf::RenderWindow* _window, std::stack<Scene*>* scenes);
	~SceneGame();

	void update(float& dt);
	void render(sf::RenderTarget* target);

private:
	Map* _map;
	Player* _player;
	InterfaceHUD* _hud;
	InterfaceShop* _shop;
	InterfaceBox* _box;
	InterfaceDeath* _death;
};

#endif SCENE_GAME_H