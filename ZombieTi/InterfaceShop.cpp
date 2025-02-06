#include "pch.h"
#include "InterfaceShop.h"

InterfaceShop::InterfaceShop(sf::RenderWindow* window, sf::Font font, Player* player, InterfaceHUD* hud) 
	: Interface(window, font), _playerReference(player), _hudReference(hud)
{
	std::cout << "InterfaceShop::InterfaceShop::Creation..." << std::endl;

	_container = new sf::RectangleShape({ 800, 500 });
	_container->setFillColor(sf::Color(120, 120, 120, 120));
	_container->setPosition(sf::Vector2f(
		window->getSize().x / 2 - _container->getGlobalBounds().size.x / 2,
		window->getSize().y / 2 - _container->getGlobalBounds().size.y / 2
	));
	
	_texts["title"] = new sf::Text(_font, "Shop", 60);
	_texts["title"]->setFillColor(sf::Color::White);
	_texts["title"]->setPosition(sf::Vector2f(
		_container->getPosition().x + 20,
		_container->getPosition().y + 10
	));

	_buttons["close"] = new Button(sf::Vector2f(
		_container->getPosition().x + _container->getGlobalBounds().size.x - 130,
		_container->getPosition().y + 10
	), _font, "Close", true);

	_texts["hpTitle"] = new sf::Text(_font, "HP", 40);
	_texts["hpTitle"]->setFillColor(sf::Color::Red);
	_texts["hpTitle"]->setPosition(sf::Vector2f(
		_container->getPosition().x + 20,
		_texts["title"]->getPosition().y + 100
	));

	_buttons["hpExchange1"] = new Button(sf::Vector2f(
		_texts["hpTitle"]->getPosition().x,
		_texts["hpTitle"]->getPosition().y + _texts["hpTitle"]->getGlobalBounds().size.y + 40
	), _font, "+25 -> 10$", true, 30);

	_buttons["hpExchange2"] = new Button(sf::Vector2f(
		_texts["hpTitle"]->getPosition().x,
		_buttons["hpExchange1"]->getShape().getPosition().y + _buttons["hpExchange1"]->getShape().getGlobalBounds().size.y + 10
	), _font, "+60 -> 25$", true, 30);

	_buttons["hpExchange3"] = new Button(sf::Vector2f(
		_texts["hpTitle"]->getPosition().x,
		_buttons["hpExchange2"]->getShape().getPosition().y + _buttons["hpExchange2"]->getShape().getGlobalBounds().size.y + 10
	), _font, "+200 -> 60$", true, 30);

	_texts["bulletsTitle"] = new sf::Text(_font, "Bullets", 40);
	_texts["bulletsTitle"]->setFillColor(sf::Color::Red);
	_texts["bulletsTitle"]->setPosition(sf::Vector2f(
		_container->getPosition().x + 400,
		_texts["title"]->getPosition().y + 100
	));

	_buttons["bulletsExchange1"] = new Button(sf::Vector2f(
		_texts["bulletsTitle"]->getPosition().x,
		_texts["bulletsTitle"]->getPosition().y + _texts["bulletsTitle"]->getGlobalBounds().size.y + 40
	), _font, "+20 -> 10$", true, 30);

	_buttons["bulletsExchange2"] = new Button(sf::Vector2f(
		_texts["bulletsTitle"]->getPosition().x,
		_buttons["bulletsExchange1"]->getShape().getPosition().y + _buttons["bulletsExchange1"]->getShape().getGlobalBounds().size.y + 10
	), _font, "+50 -> 25$", true, 30);

	_buttons["bulletsExchange3"] = new Button(sf::Vector2f(
		_texts["bulletsTitle"]->getPosition().x,
		_buttons["bulletsExchange2"]->getShape().getPosition().y + _buttons["bulletsExchange2"]->getShape().getGlobalBounds().size.y + 10
	), _font, "+130 -> 60$", true, 30);

	_buttons["luckExchange"] = new Button(sf::Vector2f(
		_container->getPosition().x + 20,
		_container->getPosition().y + _container->getGlobalBounds().size.y - 60
	), _font, "+1 luck -> 50$", true, 30);

	std::cout << "InterfaceShop::InterfaceShop::Creation done" << std::endl;
}

void InterfaceShop::update(sf::Vector2f& mousePosition)
{
	Interface::update(mousePosition);

	static bool lastClick = false;
	bool actualClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	
	if (_buttons["hpExchange1"]->isPressed() && !lastClick && actualClick && _playerReference->getMoney() >= 10)
	{
		std::cout << "SceneGame::update::25 hp bought for 10 money" << std::endl;
		_playerReference->addMoney(-10);
		_playerReference->addHp(20);
		_hudReference->refresh();
	}

	if (_buttons["hpExchange2"]->isPressed() && !lastClick && actualClick && _playerReference->getMoney() >= 25)
	{
		std::cout << "SceneGame::update::60 hp bought for 25 money" << std::endl;
		_playerReference->addMoney(-25);
		_playerReference->addHp(60);
		_hudReference->refresh();
	}

	if (_buttons["hpExchange3"]->isPressed() && !lastClick && actualClick && _playerReference->getMoney() >= 60)
	{
		std::cout << "SceneGame::update::200 hp bought for 60 money" << std::endl;
		_playerReference->addMoney(-60);
		_playerReference->addHp(200);
		_hudReference->refresh();
	}

	if (_buttons["bulletsExchange1"]->isPressed() && !lastClick && actualClick && _playerReference->getMoney() >= 10)
	{
		std::cout << "SceneGame::update::20 bullets bought for 10 money" << std::endl;
		_playerReference->addMoney(-10);
		_playerReference->addBullets(20);
		_hudReference->refresh();
	}

	if (_buttons["bulletsExchange2"]->isPressed() && !lastClick && actualClick && _playerReference->getMoney() >= 25)
	{
		std::cout << "SceneGame::update::50 bullets bought for 25 money" << std::endl;
		_playerReference->addMoney(-25);
		_playerReference->addBullets(60);
		_hudReference->refresh();
	}

	if (_buttons["bulletsExchange3"]->isPressed() && !lastClick && actualClick && _playerReference->getMoney() >= 60)
	{
		std::cout << "SceneGame::update::130 bullets bought for 60 money" << std::endl;
		_playerReference->addMoney(-60);
		_playerReference->addBullets(130);
		_hudReference->refresh();
	}

	if (
		_buttons["luckExchange"]->isPressed() && !lastClick && actualClick && 
		_playerReference->getMoney() >= 50 && _playerReference->getLuck() < 12)
	{
		std::cout << "SceneGame::update::1 luck bought for 50 money" << std::endl;
		_playerReference->addMoney(-50);
		_playerReference->addLuck(1);
		_hudReference->refresh();
	}

	if (_buttons["close"]->isPressed())
	{
		close();
	}

	lastClick = actualClick;
}

void InterfaceShop::render(sf::RenderTarget* target)
{
	Interface::render(target);
}
