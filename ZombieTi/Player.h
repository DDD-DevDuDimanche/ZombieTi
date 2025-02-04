#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Tile.h"
#include "Map.h"
#include "TextureLoader.h"
#include "Weapon.h"

class Player : public Entity
{
public:
	Player(sf::Vector2f position, Map* map);
	~Player();

	void update(float& dt, bool keyTimeReady);
	void render(sf::RenderTarget* target);

	sf::Vector2f getPosition();
	Weapon& getWeapon();
	void setWeapon(Weapon* weapon);

private:
	////////////////////////////////////////////////////////////
	/// Reference of the game map scene
	////////////////////////////////////////////////////////////
	Map* _mapReference;

	////////////////////////////////////////////////////////////
	/// Weapon of the player
	////////////////////////////////////////////////////////////
	Weapon* _weapon;

	////////////////////////////////////////////////////////////
	/// Move the sprite by a direction between -1 and 1
	////////////////////////////////////////////////////////////
	void move(sf::Vector2f direction);
};

#endif PLAYER_H