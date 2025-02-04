#include "pch.h"
#include "InterfaceBox.h"

InterfaceBox::InterfaceBox(sf::RenderWindow* window, sf::Font font, sf::Text* moneyText, int& luckReference) 
	: Interface(window, font), _moneyTextReference(moneyText), _luckReference(luckReference)
{
	std::cout << "InterfaceBox::InterfaceBox::Creation..." << std::endl;
	_container.setSize({ 800, 500 });
	_container.setFillColor(sf::Color(120, 120, 120, 120));
	_container.setPosition(sf::Vector2f(
		window->getSize().x / 2 - _container.getGlobalBounds().size.x / 2,
		window->getSize().y / 2 - _container.getGlobalBounds().size.y / 2
	));

	_texts["title"] = new sf::Text(_font, "Shop", 60);
	_texts["title"]->setFillColor(sf::Color::White);
	_texts["title"]->setPosition(sf::Vector2f(_container.getPosition().x + 20, _container.getPosition().y + 10));

	_buttons["close"] = new Button(sf::Vector2f(
		_container.getPosition().x + _container.getGlobalBounds().size.x - 130,
		_container.getPosition().y + 10
	), _font, "Close", true);
}

void InterfaceBox::update(sf::Vector2f& mousePosition)
{
	Interface::update(mousePosition);

	int money = std::stoi(_moneyTextReference->getString().toAnsiString());

	static bool lastClick = false;
	bool actualClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	lastClick = actualClick;
}

void InterfaceBox::render(sf::RenderTarget* target)
{
	Interface::render(target);
	target->draw(_container);
}
