#include "pch.h"
#include "Map.h"

sf::Vector2f Map::MAP_SIZE = { 20, 11 };

Map::Map()
{
	std::cout << "Map::Map::Creation..." << std::endl;
	int _mapIndex[11][20] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 1 },
		{ 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 1 },
		{ 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	_map.resize(MAP_SIZE.x);

	for (int y = 0; y < MAP_SIZE.y; y++)
	{
		for (int x = 0; x < MAP_SIZE.x; x++)
		{
			_map[x].resize(MAP_SIZE.y);

			switch (_mapIndex[y][x])
			{
			case 0:
				std::cout << "Map::Map::New floor tile created at position {x:" << x << ";y:" << y << "}" << std::endl;
				_map[x][y] = new Tile(sf::Vector2f(x, y), TileType::FLOOR);
				break;
			case 1:
				std::cout << "Map::Map::New wall tile created at position {x:" << x << ";y:" << y << "}" << std::endl;
				_map[x][y] = new Tile(sf::Vector2f(x, y), TileType::WALL);
				break;
			case 2:
				std::cout << "Map::Map::New zombie tile created at position {x:" << x << ";y:" << y << "}" << std::endl;
				_map[x][y] = new Tile(sf::Vector2f(x, y), TileType::ZOMBIE);
				break;
			case 3:
				std::cout << "Map::Map::New box tile created at position {x:" << x << ";y:" << y << "}" << std::endl;
				_map[x][y] = new Tile(sf::Vector2f(x, y), TileType::BOX);
				break;
			case 4:
				std::cout << "Map::Map::New shop tile created at position {x:" << x << ";y:" << y << "}" << std::endl;
				_map[x][y] = new Tile(sf::Vector2f(x, y), TileType::SHOP);
				break;
			default:
				std::cout << "Map::Map::Map Index " << _mapIndex[y][x] << " isn't supported" << std::endl;
				throw "Map::Map::Map Index isn't supported";
			}
		}
	}
	std::cout << "Map::Map::Creation Done" << std::endl;
}

Map::~Map()
{
	std::cout << "Map::~Map::Unload..." << std::endl;
	for (int y = 0; y < MAP_SIZE.y; y++)
	{
		for (int x = 0; x < MAP_SIZE.x; x++)
		{
			delete _map[x][y];
		}
	}
	std::cout << "Map::~Map::Unload done..." << std::endl;
}

void Map::render(sf::RenderTarget* target)
{
	for (int y = 0; y < MAP_SIZE.y; y++)
	{
		for (int x = 0; x < MAP_SIZE.x; x++)
		{
			if (_map[x][y] != NULL)
			{
				_map[x][y]->render(target);
			}
		}
	}
}

std::vector<std::vector<Tile*>>& Map::getMap()
{
	return _map;
}

Tile* Map::getTile(sf::Vector2f position)
{
	return _map[position.x / Tile::TILE_SIZE][position.y / Tile::TILE_SIZE];
}
