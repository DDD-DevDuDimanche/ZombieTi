#ifndef INTERFACE_BOX_H
#define INTERFACE_BOX_H

#include "Interface.h"
#include "Player.h"

class InterfaceBox : public Interface
{
public:
	InterfaceBox(sf::RenderWindow* window, sf::Font font, sf::Text* moneyText, int& luckReference, Player* playerReference);
	~InterfaceBox() {};

	void update(sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

	int getMoneyReference();

private:
	sf::RectangleShape _container;
	sf::Text* _moneyTextReference;
	int& _luckReference;
	Player* _playerReference;
	bool _purchaseDone;
	Weapon* _weaponGenerated;

	void reset();
};

#endif INTERFACE_BOX_H