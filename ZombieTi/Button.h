#pragma once
#ifndef BUTTON_H
#define BUTTON_H

enum ButtonState
{
	IDLE,
	HOVER,
	PRESSED,
};

class Button
{
public:
	Button(sf::Vector2f position, sf::Font& font, std::string text, bool border = false, int size = 45);
	~Button() {};

	void update(sf::Vector2f& mousePosition);
	void render(sf::RenderTarget* target);

	bool isPressed();
	sf::RectangleShape getShape();

private:
	////////////////////////////////////////////////////////////
	/// Actual state of the button
	////////////////////////////////////////////////////////////
	ButtonState _state;

	sf::RectangleShape _shape;
	sf::Text _text;

	////////////////////////////////////////////////////////////
	/// Default color for the button text
	////////////////////////////////////////////////////////////
	sf::Color _idleTextColor;

	////////////////////////////////////////////////////////////
	/// Color for the button text when hovered
	////////////////////////////////////////////////////////////
	sf::Color _hoverTextColor;
};

#endif BUTTON_H