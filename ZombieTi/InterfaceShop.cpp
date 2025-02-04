#include "pch.h"
#include "InterfaceShop.h"

InterfaceShop::InterfaceShop(sf::RenderWindow* window, sf::Font font, sf::Text* moneyText, sf::Text* hpText, sf::Text* bulletsText, int& luckReference)
	: Interface(window, font), _moneyReference(moneyText), _hpReference(hpText), _bulletsReference(bulletsText), _luckReference(luckReference)
{
	std::cout << "InterfaceShop::InterfaceShop::Creation..." << std::endl;

	_container.setSize({ 800, 500 });
	_container.setFillColor(sf::Color(120, 120, 120, 120));
	_container.setPosition(sf::Vector2f(
		window->getSize().x / 2 - _container.getGlobalBounds().size.x / 2,
		window->getSize().y / 2 - _container.getGlobalBounds().size.y / 2
	));
	
	_texts["title"] = new sf::Text(_font);
	_texts["title"]->setFillColor(sf::Color::White);
	_texts["title"]->setCharacterSize(60);
	_texts["title"]->setString("Shop");
	_texts["title"]->setPosition(sf::Vector2f(
		_container.getPosition().x + 20,
		_container.getPosition().y + 10
	));

	_buttons["close"] = new Button(sf::Vector2f(
		_container.getPosition().x + _container.getGlobalBounds().size.x - 130,
		_container.getPosition().y + 10
	), _font, "Close", true);

	_texts["hpTitle"] = new sf::Text(_font);
	_texts["hpTitle"]->setFillColor(sf::Color::Red);
	_texts["hpTitle"]->setCharacterSize(40);
	_texts["hpTitle"]->setString("HP");
	_texts["hpTitle"]->setPosition(sf::Vector2f(
		_container.getPosition().x + 20,
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

	_texts["bulletsTitle"] = new sf::Text(_font);
	_texts["bulletsTitle"]->setFillColor(sf::Color::Red);
	_texts["bulletsTitle"]->setCharacterSize(40);
	_texts["bulletsTitle"]->setString("Bullets");
	_texts["bulletsTitle"]->setPosition(sf::Vector2f(
		_container.getPosition().x + 400,
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
		_container.getPosition().x + 20,
		_container.getPosition().y + _container.getGlobalBounds().size.y - 60
	), _font, "+1 luck -> 50$", true, 30);

	std::cout << "InterfaceShop::InterfaceShop::Creation done" << std::endl;
}

void InterfaceShop::update(sf::Vector2f& mousePosition)
{
	Interface::update(mousePosition);

	int money = std::stoi(_moneyReference->getString().toAnsiString());
	int hp = std::stoi(_hpReference->getString().toAnsiString());
	int bullets = std::stoi(_bulletsReference->getString().toAnsiString());

	static bool lastClick = false;
	bool actualClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	
	if (_buttons["hpExchange1"]->isPressed() && !lastClick && actualClick && money >= 10)
	{
		std::cout << "SceneGame::update::25 hp bought for 10 money" << std::endl;
		_moneyReference->setString(std::to_string(money - 10));
		_hpReference->setString(std::to_string(hp + 25));
	}

	if (_buttons["hpExchange2"]->isPressed() && !lastClick && actualClick && money >= 25)
	{
		std::cout << "SceneGame::update::60 hp bought for 25 money" << std::endl;
		_moneyReference->setString(std::to_string(money - 25));
		_hpReference->setString(std::to_string(hp + 60));
	}

	if (_buttons["hpExchange3"]->isPressed() && !lastClick && actualClick && money >= 60)
	{
		std::cout << "SceneGame::update::200 hp bought for 60 money" << std::endl;
		_moneyReference->setString(std::to_string(money - 60));
		_hpReference->setString(std::to_string(hp + 200));
	}

	if (_buttons["bulletsExchange1"]->isPressed() && !lastClick && actualClick && money >= 10)
	{
		std::cout << "SceneGame::update::20 bullets bought for 10 money" << std::endl;
		_moneyReference->setString(std::to_string(money - 10));
		_bulletsReference->setString(std::to_string(bullets + 20));
	}

	if (_buttons["bulletsExchange2"]->isPressed() && !lastClick && actualClick && money >= 25)
	{
		std::cout << "SceneGame::update::50 bullets bought for 25 money" << std::endl;
		_moneyReference->setString(std::to_string(money - 25));
		_bulletsReference->setString(std::to_string(bullets + 60));
	}

	if (_buttons["bulletsExchange3"]->isPressed() && !lastClick && actualClick && money >= 60)
	{
		std::cout << "SceneGame::update::130 bullets bought for 60 money" << std::endl;
		_moneyReference->setString(std::to_string(money - 60));
		_bulletsReference->setString(std::to_string(bullets + 130));
	}

	if (_buttons["luckExchange"]->isPressed() && !lastClick && actualClick && money >= 50 && _luckReference < 12)
	{
		std::cout << "SceneGame::update::1 luck bought for 50 money" << std::endl;
		_moneyReference->setString(std::to_string(money - 50));
		_luckReference++;
	}

	lastClick = actualClick;
}

void InterfaceShop::render(sf::RenderTarget* target)
{
	Interface::render(target);
	target->draw(_container);
}
