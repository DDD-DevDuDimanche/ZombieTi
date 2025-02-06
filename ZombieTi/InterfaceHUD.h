#pragma once
#ifndef INTERFACE_HUD_H
#define INTERFACE_HUD_H

#include "Interface.h"
#include "Player.h"
#include "Tile.h"
#include "TextureLoader.h"

class InterfaceHUD : public Interface
{
public:
	InterfaceHUD(sf::RenderWindow*, sf::Font font, Player* player);
	~InterfaceHUD();

	void render(sf::RenderTarget* target);

	void refresh();

private:
	Player* _playerReference;
	sf::Text* _moneyText;
	sf::RectangleShape* _moneyIcon;
	sf::Text* _hpText;
	sf::RectangleShape* _hpIcon;
	sf::Text* _bulletsText;
	sf::RectangleShape* _bulletsIcon;
	sf::Text* _weaponText;
};

#endif INTERFACE_HUD_H