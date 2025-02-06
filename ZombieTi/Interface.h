#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include "Button.h";

class Interface
{
public:
	Interface(sf::RenderWindow* window, sf::Font font, bool showBackground = true);
	virtual ~Interface();

	void update(sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

	std::map<std::string, Button*>& getButtons();
	void open();
	void close();
	const bool& isVisible();

protected:
	////////////////////////////////////////////////////////////
	/// Buttons inside the interface
	////////////////////////////////////////////////////////////
	std::map<std::string, Button*> _buttons;
	std::map<std::string, sf::Text*> _texts;
	sf::Font _font;
	sf::RectangleShape* _container;

private:
	////////////////////////////////////////////////////////////
	/// Background around the interface container
	////////////////////////////////////////////////////////////
	sf::RectangleShape _background;
	bool _visible;
	bool _showBackground;
};

#endif INTERFACE_H