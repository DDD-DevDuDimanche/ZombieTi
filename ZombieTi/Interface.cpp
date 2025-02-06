#include "pch.h"
#include "Interface.h"

Interface::Interface(sf::RenderWindow* window, sf::Font font, bool showBackground) : _font(font), _visible(false), _showBackground(showBackground)
{
	_background.setSize(sf::Vector2f((float) window->getSize().x, (float) window->getSize().y));
	_background.setFillColor(sf::Color(20, 20, 20, 200));
	_container = NULL;
}

Interface::~Interface()
{
	for (auto index = _buttons.begin(); index != _buttons.end(); ++index) {
		delete index->second;
	}

	for (auto index = _texts.begin(); index != _texts.end(); ++index) {
		delete index->second;
	}

	delete _container;
}

void Interface::update(sf::Vector2f& mousePosition)
{
	for (auto& index : _buttons) {
		index.second->update(mousePosition);
	}
}

void Interface::render(sf::RenderTarget* target)
{
	if (_showBackground)
	{
		target->draw(_background);
	}

	if (_container != NULL)
	{
		target->draw(*_container);
	}

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

void Interface::open()
{
	_visible = true;
}

void Interface::close()
{
	_visible = false;
}

const bool& Interface::isVisible()
{
	return _visible;
}
