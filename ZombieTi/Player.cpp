#include "pch.h"
#include "Player.h"

Player::Player(sf::Vector2f position, Map* map) : _money(0), _hp(20), _bullets(10), _luck(0)
{
	std::cout << "Player::Player::Creation..." << std::endl;
	_sprite = new sf::Sprite(TextureLoader::loadTexture("Assets/player.png"));
	std::cout << "Player::Player::Texture loaded" << std::endl;
	_sprite->setPosition(position);
	_mapReference = map;
	_weapon = new Weapon(Weapon::WeaponData[0].getName(), Weapon::WeaponData[0].getDamage());
	std::cout << "Player::Player::Creation done" << std::endl;
}

Player::~Player()
{
	delete _weapon;
	std::cout << "Player::~Player::Unload done" << std::endl;
}

void Player::update(float& dt, bool keyTimeReady)
{
	Entity::update(dt);

	// Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && keyTimeReady)
	{
		move({ -1, 0 });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && keyTimeReady)
	{
		move({ 1, 0 });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && keyTimeReady)
	{
		move({ 0, -1 });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && keyTimeReady)
	{
		move({ 0, 1 });
	}
}

void Player::render(sf::RenderTarget* target)
{
	Entity::render(target);
}

sf::Vector2f Player::getPosition()
{
	return _sprite->getPosition();
}

Weapon& Player::getWeapon()
{
	return *_weapon;
}

void Player::setWeapon(Weapon* weapon)
{
	_weapon = weapon;
}

int& Player::getMoney()
{
	return _money;
}

int& Player::getHp()
{
	return _hp;
}

int& Player::getBullets()
{
	return _bullets;
}

int& Player::getLuck()
{
	return _luck;
}

void Player::addMoney(int amount)
{
	_money += amount;
}

void Player::addHp(int amount)
{
	_hp += amount;
}

void Player::addBullets(int amount)
{
	_bullets += amount;
}

void Player::addLuck(int amount)
{
	_luck += amount;
}

void Player::move(sf::Vector2f direction)
{
	sf::Vector2f newPosition = sf::Vector2f(
		_sprite->getPosition().x + Tile::TILE_SIZE * direction.x,
		_sprite->getPosition().y + Tile::TILE_SIZE * direction.y
	);

	if (_mapReference->getTile(sf::Vector2f(newPosition.x, newPosition.y))->getType() == TileType::WALL) {
		std::cout << "Player::move::Player can't move toward the position {x:" << newPosition.x / 64 << ";y:" << newPosition.y / 64 << "} due to a wall" << std::endl;
		return;
	}

	std::cout << "Player::move::Player moved to position {x:" << newPosition.x / 64 << ";y:" << newPosition.y / 64 << "}" << std::endl;
	_sprite->setPosition(newPosition);
}
