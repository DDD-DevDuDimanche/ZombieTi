#pragma once
#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void update(float& dt);
	void render(sf::RenderTarget* target);

protected:
	sf::Sprite* _sprite;
};

#endif ENTITY_H