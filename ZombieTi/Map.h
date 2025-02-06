#pragma once
#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class Map
{
public:
	Map();
	~Map();

	void render(sf::RenderTarget* target);

	std::vector<std::vector<Tile*>>& getMap();
	Tile* getTile(sf::Vector2f position);
	
private:
	////////////////////////////////////////////////////////////
	/// Map size settings for the game
	////////////////////////////////////////////////////////////
	sf::Vector2f static MAP_SIZE;

	////////////////////////////////////////////////////////////
	/// Map with each Tile data
	////////////////////////////////////////////////////////////
	std::vector<std::vector<Tile*>> _map;
};

#endif MAP_H