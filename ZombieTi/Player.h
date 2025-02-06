#pragma once
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

	int& getMoney();
	int& getHp();
	int& getBullets();
	int& getLuck();

	void addMoney(int amount);
	void addHp(int amount);
	void addBullets(int amount);
	void addLuck(int amount);

private:
	////////////////////////////////////////////////////////////
	/// Reference of the game map scene
	////////////////////////////////////////////////////////////
	Map* _mapReference;

	Weapon* _weapon;
	int _money;
	int _hp;
	int _bullets;
	int _luck;

	////////////////////////////////////////////////////////////
	/// Move the sprite by a direction between -1 and 1
	////////////////////////////////////////////////////////////
	void move(sf::Vector2f direction);
};

#endif PLAYER_H