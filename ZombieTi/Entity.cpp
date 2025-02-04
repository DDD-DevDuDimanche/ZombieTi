#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	delete _sprite;
}

void Entity::update(float& dt)
{
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(*_sprite);
}
