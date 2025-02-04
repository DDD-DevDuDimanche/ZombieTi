#ifndef INTERFACE_DEATH_H
#define INTERFACE_DEATH_H

#include "Interface.h"

class InterfaceDeath : public Interface
{
public:
	InterfaceDeath(sf::RenderWindow* window, sf::Font font);
	~InterfaceDeath() {};

	void update(sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

private:
	sf::RectangleShape _container;
};

#endif INTERFACE_DEATH_H