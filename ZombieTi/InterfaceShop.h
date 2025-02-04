#ifndef INTERFACE_SHOP_H
#define INTERFACE_SHOP_H

#include "Interface.h"

class InterfaceShop : public Interface
{
public:
	InterfaceShop(sf::RenderWindow* window, sf::Font font, sf::Text* moneyText, sf::Text* hpText, sf::Text* bulletsText, int& luckReference);
	~InterfaceShop() {};

	void update(sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

private:
	sf::RectangleShape _container;
	sf::Text* _moneyReference;
	sf::Text* _hpReference;
	sf::Text* _bulletsReference;
	int& _luckReference;
};

#endif INTERFACE_SHOP_H