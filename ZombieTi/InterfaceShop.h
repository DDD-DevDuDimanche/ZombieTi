#pragma once
#ifndef INTERFACE_SHOP_H
#define INTERFACE_SHOP_H

#include "Player.h"
#include "InterfaceHUD.h"

class InterfaceShop : public Interface
{
public:
	InterfaceShop(sf::RenderWindow* window, sf::Font font, Player* player, InterfaceHUD* hud);
	~InterfaceShop() {};

	void update(sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

private:
	Player* _playerReference;
	InterfaceHUD* _hudReference;
};

#endif INTERFACE_SHOP_H