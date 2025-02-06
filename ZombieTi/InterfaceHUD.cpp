#include "pch.h"
#include "InterfaceHUD.h"

InterfaceHUD::InterfaceHUD(sf::RenderWindow* window, sf::Font font, Player* player)
	: Interface(window, font, false), _playerReference(player)
{
	std::cout << "InterfaceHUD::InterfaceHUD::Creation..." << std::endl;

	// Money
	_moneyText = new sf::Text(_font, std::to_string(_playerReference->getMoney()), 40);
	_moneyText->setFillColor(sf::Color::White);
	_moneyText->setPosition({ Tile::TILE_SIZE + 10, window->getSize().y - Tile::TILE_SIZE });

	_moneyIcon = new sf::RectangleShape({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_moneyIcon->setPosition({ 0, window->getSize().y - Tile::TILE_SIZE });
	_moneyIcon->setTexture(&TextureLoader::loadTexture("Assets/icon_money.png"));
	std::cout << "InterfaceHUD::InterfaceHUD::Money Texture loaded" << std::endl;

	// Life
	_hpText = new sf::Text(_font, std::to_string(_playerReference->getHp()), 40);
	_hpText->setFillColor(sf::Color::White);
	_hpText->setPosition({ Tile::TILE_SIZE * 5 + 10, window->getSize().y - Tile::TILE_SIZE });

	_hpIcon = new sf::RectangleShape({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_hpIcon->setPosition({ Tile::TILE_SIZE * 4, window->getSize().y - Tile::TILE_SIZE });
	_hpIcon->setTexture(&TextureLoader::loadTexture("Assets/icon_hp.png"));
	std::cout << "InterfaceHUD::InterfaceHUD::HP Texture loaded" << std::endl;

	// Bullets
	_bulletsText = new sf::Text(_font, std::to_string(_playerReference->getBullets()), 40);
	_bulletsText->setFillColor(sf::Color::White);
	_bulletsText->setPosition({ Tile::TILE_SIZE * 8 + 10, window->getSize().y - Tile::TILE_SIZE });

	_bulletsIcon = new sf::RectangleShape({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_bulletsIcon->setPosition({ Tile::TILE_SIZE * 7, window->getSize().y - Tile::TILE_SIZE });
	_bulletsIcon->setTexture(&TextureLoader::loadTexture("Assets/icon_bullets.png"));
	std::cout << "InterfaceHUD::InterfaceHUD::Bullets Texture loaded" << std::endl;

	// Weapon
	_weaponText = new sf::Text(
		_font, 
		_playerReference->getWeapon().getName() + " (" + std::to_string(_playerReference->getWeapon().getDamage()) + ")", 
		40
	);
	_weaponText->setFillColor(sf::Color::White);
	_weaponText->setPosition({ Tile::TILE_SIZE * 9 + 10, window->getSize().y - Tile::TILE_SIZE });

	std::cout << "InterfaceHUD::InterfaceHUD::Creation done" << std::endl;
}

InterfaceHUD::~InterfaceHUD()
{
	delete _moneyText;
	delete _moneyIcon;
	delete _hpText;
	delete _hpIcon;
	delete _bulletsText;
	delete _bulletsIcon;
	delete _weaponText;
}

void InterfaceHUD::render(sf::RenderTarget* target)
{
	Interface::render(target);
	target->draw(*_moneyText);
	target->draw(*_moneyIcon);
	target->draw(*_hpText);
	target->draw(*_hpIcon);
	target->draw(*_bulletsText);
	target->draw(*_bulletsIcon);
	target->draw(*_weaponText);
}

void InterfaceHUD::refresh()
{
	_moneyText->setString(std::to_string(_playerReference->getMoney()));
	_hpText->setString(std::to_string(_playerReference->getHp()));
	_bulletsText->setString(std::to_string(_playerReference->getBullets()));
	_weaponText->setString(_playerReference->getWeapon().getName() + " (" + std::to_string(_playerReference->getWeapon().getDamage()) + ")");
}
