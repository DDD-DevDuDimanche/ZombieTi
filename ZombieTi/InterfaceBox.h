#pragma once
#ifndef INTERFACE_BOX_H
#define INTERFACE_BOX_H

#include "InterfaceHUD.h"
#include "Player.h"

class InterfaceBox : public Interface
{
public:
	InterfaceBox(sf::RenderWindow* window, sf::Font font, Player* player, InterfaceHUD* hud);
	~InterfaceBox();

	void update(sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

	int getMoneyReference();

private:
	Player* _playerReference;
	InterfaceHUD* _hudReference;
	bool _purchaseDone;
	Weapon* _weaponGenerated;

	void reset();
};

#endif INTERFACE_BOX_H