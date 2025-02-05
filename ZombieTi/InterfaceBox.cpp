#include "pch.h"
#include "InterfaceBox.h"

InterfaceBox::InterfaceBox(sf::RenderWindow* window, sf::Font font, Player* player, InterfaceHUD* hud)
	: Interface(window, font), _playerReference(player), _hudReference(hud)
{
	std::cout << "InterfaceBox::InterfaceBox::Creation..." << std::endl;
	_container = new sf::RectangleShape({ 800, 500 });
	_container->setFillColor(sf::Color(120, 120, 120, 120));
	_container->setPosition(sf::Vector2f(
		window->getSize().x / 2 - _container->getGlobalBounds().size.x / 2,
		window->getSize().y / 2 - _container->getGlobalBounds().size.y / 2
	));

	_texts["title"] = new sf::Text(_font, "Box", 60);
	_texts["title"]->setFillColor(sf::Color::White);
	_texts["title"]->setPosition(sf::Vector2f(_container->getPosition().x + 20, _container->getPosition().y + 10));

	_texts["luck"] = new sf::Text(_font, "Luck : " + std::to_string(_playerReference->getLuck()), 30);
	_texts["luck"]->setFillColor(sf::Color::White);
	_texts["luck"]->setPosition(sf::Vector2f(
		_container->getPosition().x + _container->getGlobalBounds().size.x / 2 - _texts["luck"]->getGlobalBounds().size.x / 2,
		_container->getPosition().y + 30
	));

	_texts["weapon"] = new sf::Text(_font, "", 50);
	_texts["weapon"]->setFillColor(sf::Color::Blue);

	_buttons["close"] = new Button(sf::Vector2f(
		_container->getPosition().x + _container->getGlobalBounds().size.x - 130,
		_container->getPosition().y + 10
	), _font, "Close", true);

	_purchaseDone = false;
	_weaponGenerated = NULL;

	_buttons["exchange"] = new Button(sf::Vector2f(
		_container->getPosition().x + _container->getGlobalBounds().size.x / 2 - 100,
		_container->getPosition().y + _container->getGlobalBounds().size.y - 80
	), _font, "Buy -> 30$", true);
}

InterfaceBox::~InterfaceBox()
{
	delete _weaponGenerated;
}

void InterfaceBox::update(sf::Vector2f& mousePosition)
{
	Interface::update(mousePosition);

	static bool lastClick = false;
	bool actualClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	if (_buttons.count("exchange") && _buttons["exchange"]->isPressed() && !lastClick && actualClick && _playerReference->getMoney() >= 30)
	{
		// Get a roll between 0 and 3
		int randomRoll = (rand() % 4) + _playerReference->getLuck();
		_weaponGenerated = new Weapon(Weapon::WeaponData[randomRoll].getName(), Weapon::WeaponData[randomRoll].getDamage());
		_texts["weapon"]->setString(_weaponGenerated->getName() + " (" + std::to_string(_weaponGenerated->getDamage()) + ")");
		_texts["weapon"]->setPosition(sf::Vector2f(
			_container->getPosition().x + _container->getGlobalBounds().size.x / 2 - _texts["weapon"]->getGlobalBounds().size.x / 2,
			_container->getPosition().y + _container->getGlobalBounds().size.y / 2 - _texts["weapon"]->getGlobalBounds().size.y / 2
		));
		_playerReference->addMoney(-30);
		_purchaseDone = true;
		_hudReference->refresh();
	}

	if (_buttons.count("confirm") && _buttons["confirm"]->isPressed() && !lastClick && actualClick)
	{
		_playerReference->setWeapon(_weaponGenerated);
		reset();
	}

	if ((_buttons["close"]->isPressed() || (_buttons.count("cancel") && _buttons["cancel"]->isPressed())) && !lastClick && actualClick)
	{
		reset();
	}

	if (_purchaseDone)
	{
		_buttons["confirm"] = new Button(sf::Vector2f(
			_container->getPosition().x + 20,
			_container->getPosition().y + _container->getGlobalBounds().size.y - 70
		), _font, "Confirm", true);

		_buttons["cancel"] = new Button(sf::Vector2f(
			_container->getPosition().x + _container->getGlobalBounds().size.x - 150,
			_container->getPosition().y + _container->getGlobalBounds().size.y - 70
		), _font, "Cancel", true);

		_buttons.erase("exchange");
	}

	lastClick = actualClick;
}

void InterfaceBox::render(sf::RenderTarget* target)
{
	Interface::render(target);
}

void InterfaceBox::reset()
{
	_texts["weapon"]->setString("");
	_weaponGenerated = NULL;
	_purchaseDone = false;
	_buttons.erase("confirm");
	_buttons.erase("cancel");
	_buttons["exchange"] = new Button(sf::Vector2f(
		_container->getPosition().x + _container->getGlobalBounds().size.x / 2 - 100,
		_container->getPosition().y + _container->getGlobalBounds().size.y - 80
	), _font, "Buy -> 30$", true);
	_hudReference->refresh();
	close();
}
