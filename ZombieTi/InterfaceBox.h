#ifndef INTERFACE_BOX_H
#define INTERFACE_BOX_H

#include "Interface.h"

class InterfaceBox : public Interface
{
public:
	InterfaceBox(sf::RenderWindow* window, sf::Font font, sf::Text* moneyText, int& luckReference);
	~InterfaceBox() {};

	void update(sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

	int getMoneyReference();

private:
	sf::RectangleShape _container;
	sf::Text* _moneyTextReference;
	int& _luckReference;
	bool _purchaseDone;

	void reset();
};

#endif INTERFACE_BOX_H