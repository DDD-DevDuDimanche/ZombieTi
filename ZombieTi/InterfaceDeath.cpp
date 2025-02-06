#include "pch.h"
#include "InterfaceDeath.h"

InterfaceDeath::InterfaceDeath(sf::RenderWindow* window, sf::Font font) : Interface(window, font)
{
	_container = new sf::RectangleShape({ 800, 500 });
	_container->setFillColor(sf::Color(120, 120, 120, 120));
	_container->setPosition(sf::Vector2f(
		window->getSize().x / 2 - _container->getGlobalBounds().size.x / 2,
		window->getSize().y / 2 - _container->getGlobalBounds().size.y / 2
	));

	_texts["death"] = new sf::Text(_font, "You are dead", 80);
	_texts["death"]->setFillColor(sf::Color::Red);
	_texts["death"]->setPosition(_container->getGlobalBounds().getCenter() - _texts["death"]->getGlobalBounds().size / 2.f);

	_buttons["close"] = new Button(sf::Vector2f(
		_container->getPosition().x + _container->getGlobalBounds().size.x / 2 - 70,
		_container->getPosition().y + _container->getGlobalBounds().size.y - 80
	), _font, "End", true);
}

void InterfaceDeath::update(sf::Vector2f& mousePosition)
{
	Interface::update(mousePosition);
}

void InterfaceDeath::render(sf::RenderTarget* target)
{
	Interface::render(target);
}
