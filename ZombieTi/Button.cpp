#include "pch.h"
#include "Button.h"

Button::Button(sf::Vector2f position, sf::Font& font, std::string text, bool border, int size) : _text(font)
{
	_idleTextColor = sf::Color(180, 180, 180, 255);
	_hoverTextColor = sf::Color(255, 255, 255, 255);

	_shape.setPosition(position);
	_shape.setFillColor(sf::Color::Transparent);
	_state = ButtonState::IDLE;
	_text.setString(text);
	_text.setFillColor(_idleTextColor);
	_text.setCharacterSize(size);
	_text.setLetterSpacing(2);
	_text.setOrigin(_text.getGlobalBounds().size / 2.f + _text.getLocalBounds().position);
	_shape.setSize({ _text.getGlobalBounds().size.x + 20, _text.getGlobalBounds().size.y + 20 });
	_text.setPosition(_shape.getPosition() + _shape.getSize() / 2.f);

	if (border)
	{
		_shape.setOutlineThickness(5);
		_shape.setOutlineColor(sf::Color::Black);
	}
}

void Button::update(sf::Vector2f& mousePosition)
{
	_state = ButtonState::IDLE;

	if (_shape.getGlobalBounds().contains(mousePosition))
	{
		_state = ButtonState::HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			_state = ButtonState::PRESSED;
		}
	}

	if (_state == ButtonState::IDLE)
	{
		_text.setFillColor(_idleTextColor);
	} 
	else
	{
		_text.setFillColor(_hoverTextColor);
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(_shape);
	target->draw(_text);
}

bool Button::isPressed()
{
	return _state == ButtonState::PRESSED;
}

sf::RectangleShape Button::getShape()
{
	return _shape;
}
