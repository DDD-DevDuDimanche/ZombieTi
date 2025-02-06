#pragma once
#ifndef TILE_H
#define TILE_H

#include "TextureLoader.h"

enum TileType
{
	WALL,
	FLOOR,
	ZOMBIE,
	BOX,
	SHOP
};

class Tile
{
public:
	////////////////////////////////////////////////////////////
	/// Size of every tile of the game
	////////////////////////////////////////////////////////////
	static float TILE_SIZE;

	Tile(sf::Vector2f position, TileType type);
	~Tile() {};

	void render(sf::RenderTarget* target);

	TileType& getType();

private:
	////////////////////////////////////////////////////////////
	/// Type of the tyle
	////////////////////////////////////////////////////////////
	TileType _type;

	sf::RectangleShape _shape;
};

#endif TILE_H