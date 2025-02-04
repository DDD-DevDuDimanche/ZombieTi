#include "pch.h"
#include "Interface.h"

Interface::Interface(sf::RenderWindow* window, sf::Font font) : _font(font)
{
	_background.setSize(sf::Vector2f((float) window->getSize().x, (float) window->getSize().y));
	_background.setFillColor(sf::Color(20, 20, 20, 200));
}

Interface::~Interface()
{
	for (auto index = _buttons.begin(); index != _buttons.end(); ++index) {
		delete index->second;
	}

	for (auto index = _texts.begin(); index != _texts.end(); ++index) {
		delete index->second;
	}
}

void Interface::update(sf::Vector2f& mousePosition)
{
	for (auto& index : _buttons) {
		index.second->update(mousePosition);
	}
}

void Interface::render(sf::RenderTarget* target)
{
	target->draw(_background);

	for (auto& index : _buttons) {
		index.second->render(target);
	}

	for (auto& index : _texts) {
		target->draw(*index.second);
	}
}

std::map<std::string, Button*>& Interface::getButtons()
{
	return _buttons;
}
