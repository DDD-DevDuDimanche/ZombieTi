#include "pch.h"
#include "Tile.h"

float Tile::TILE_SIZE = 64;

Tile::Tile(sf::Vector2f position, TileType type)
{
	_shape.setSize({ TILE_SIZE, TILE_SIZE });
	_shape.setFillColor(sf::Color::White);
	_shape.setPosition({ position.x * TILE_SIZE, position.y * TILE_SIZE });
	_type = type;

	std::string textureName;

	switch (type)
	{
	case TileType::WALL:
		textureName = "block_wall.png";
		break;
	case TileType::FLOOR:
		textureName = "block_floor.png";
		break;
	case TileType::ZOMBIE:
		textureName = "block_zombie.png";
		break;
	case TileType::BOX:
		textureName = "block_box.png";
		break;
	case TileType::SHOP:
		textureName = "block_shop.png";
		break;
	default:
		std::cout << "Tile::Tile::Type " << type << "not correct !" << std::endl;
		throw "Tile::Tile::Type not correct !";
		break;
	}

	_shape.setTexture(&TextureLoader::loadTexture("Assets/" + textureName));
}

void Tile::render(sf::RenderTarget* target)
{
	target->draw(_shape);
}

TileType& Tile::getType()
{
	return _type;
}
