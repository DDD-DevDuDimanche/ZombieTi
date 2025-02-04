#include "pch.h"
#include "SceneGame.h"

SceneGame::SceneGame(sf::RenderWindow* _window, std::stack<Scene*>* scenes) 
	: Scene(_window, scenes), _moneyText(_font), _hpText(_font), _bulletsText(_font), _weaponText(_font)
{
	std::cout << "SceneGame::SceneGame::Creation..." << std::endl;
	_background = new sf::RectangleShape(sf::Vector2f(_windowReference->getSize().x, _windowReference->getSize().y));
	_background->setTexture(&TextureLoader::loadTexture("Assets/game_background.png"));
	std::cout << "SceneGame::SceneGame::Background Texture loaded" << std::endl;
	_map = new Map();
	_player = new Player(sf::Vector2f(Tile::TILE_SIZE * 9, Tile::TILE_SIZE * 5), _map);
	_showShop = false;
	_showBox = false;
	_showDeath = false;

	_moneyText.setCharacterSize(40);
	_moneyText.setFillColor(sf::Color::White);
	_moneyText.setString(std::to_string(0));
	_moneyText.setPosition({ Tile::TILE_SIZE + 10, _windowReference->getSize().y - Tile::TILE_SIZE });
	_moneyShape.setSize({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_moneyShape.setPosition({ 0, _windowReference->getSize().y - Tile::TILE_SIZE });
	_moneyShape.setTexture(&TextureLoader::loadTexture("Assets/icon_money.png"));
	std::cout << "SceneGame::SceneGame::Money Texture loaded" << std::endl;

	_hpText.setCharacterSize(40);
	_hpText.setFillColor(sf::Color::White);
	_hpText.setString(std::to_string(30));
	_hpText.setPosition({ Tile::TILE_SIZE * 5 + 10, _windowReference->getSize().y - Tile::TILE_SIZE });
	_hpShape.setSize({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_hpShape.setTexture(&TextureLoader::loadTexture("Assets/icon_hp.png"));
	_hpShape.setPosition({ Tile::TILE_SIZE * 4, _windowReference->getSize().y - Tile::TILE_SIZE });
	std::cout << "SceneGame::SceneGame::HP Texture loaded" << std::endl;

	_bulletsText.setCharacterSize(40);
	_bulletsText.setFillColor(sf::Color::White);
	_bulletsText.setString(std::to_string(10));
	_bulletsText.setPosition({ Tile::TILE_SIZE * 8 + 10, _windowReference->getSize().y - Tile::TILE_SIZE });
	_bulletsShape.setSize({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_bulletsShape.setTexture(&TextureLoader::loadTexture("Assets/icon_bullets.png"));
	_bulletsShape.setPosition({ Tile::TILE_SIZE * 7, _windowReference->getSize().y - Tile::TILE_SIZE });
	std::cout << "SceneGame::SceneGame::Bullets Texture loaded" << std::endl;

	_weaponText.setCharacterSize(40);
	_weaponText.setFillColor(sf::Color::White);
	_weaponText.setString(_player->getWeapon().getName());
	_weaponText.setPosition({ Tile::TILE_SIZE * 9 + 10, _windowReference->getSize().y - Tile::TILE_SIZE });

	_luck = 0;
	std::cout << "SceneGame::SceneGame::Creation done" << std::endl;

	_shop = new InterfaceShop(_windowReference, _font, &_moneyText, &_hpText, &_bulletsText, _luck);
	_box = new InterfaceBox(_windowReference, _font, &_moneyText, _luck, _player);
	_death = new InterfaceDeath(_windowReference, _font);
}

SceneGame::~SceneGame()
{
	std::cout << "SceneGame::~SceneGame::Unload..." << std::endl;
	delete _map;
	delete _player;
	delete _shop;
	delete _box;
	std::cout << "SceneGame::~SceneGame::Unload done" << std::endl;
}

void SceneGame::update(float& dt)
{
	Scene::update(dt);

	int money = std::stoi(_moneyText.getString().toAnsiString());
	int hp = std::stoi(_hpText.getString().toAnsiString());
	int bullets = std::stoi(_bulletsText.getString().toAnsiString());

	if (!_showShop && !_showBox && !_showDeath)
	{
		// Player movement
		_player->update(dt, getKeyTimeDelay());

		// Player interaction
		static bool lastInteraction = false;
		bool actualInteraction = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);

		if (!lastInteraction && actualInteraction)
		{
			switch (_map->getTile(_player->getPosition())->getType())
			{
			case TileType::ZOMBIE:
				std::cout << "SceneGame::update::Interaction with Zombie Tile" << std::endl;
				if (bullets > 0)
				{
					_moneyText.setString(std::to_string(money + _player->getWeapon().getDamage()));
					_hpText.setString(std::to_string(hp - 2));
					_bulletsText.setString(std::to_string(bullets - 1));
				}
				break;
			case TileType::BOX:
				std::cout << "SceneGame::update::Interaction with Box Tile" << std::endl;
				_showBox = true;
				break;
			case TileType::SHOP:
				std::cout << "SceneGame::update::Interaction with Shop Tile" << std::endl;
				_showShop = true;
				break;
			default:
				std::cout << "SceneGame::update::Interaction with nothing" << std::endl;
			}
		}

		lastInteraction = actualInteraction;
	}

	if (_showShop)
	{
		_shop->update(_mousePositionView);

		if (_shop->getButtons()["close"]->isPressed())
		{
			_showShop = false;
		}
	}

	if (_showBox)
	{
		_box->update(_mousePositionView);

		if (_box->getButtons()["close"]->isPressed() || 
			(_box->getButtons().count("confirm") && _box->getButtons()["confirm"]->isPressed()) ||
			(_box->getButtons().count("cancel") && _box->getButtons()["cancel"]->isPressed()))
		{
			_box->getButtons().erase("confirm");
			_box->getButtons().erase("cancel");
			_weaponText.setString(_player->getWeapon().getName());
			_showBox = false;
		}
	}

	if (hp <= 0)
	{
		_showDeath = true;
		_death->update(_mousePositionView);

		if (_death->getButtons()["close"]->isPressed())
		{
			std::cout << "SceneGame::update::End of the game" << std::endl;
			_closeSignal = true;
		}
	}

	// Key to exit the game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		_closeSignal = true;
	}
}

void SceneGame::render(sf::RenderTarget* target)
{
	target->draw(*_background);
	_map->render(target);
	_player->render(target);
	target->draw(_moneyShape);
	target->draw(_moneyText);
	target->draw(_hpShape);
	target->draw(_hpText);
	target->draw(_bulletsShape);
	target->draw(_bulletsText);
	target->draw(_weaponText);
	
	if (_showShop)
	{
		_shop->render(target);
	}

	if (_showBox)
	{
		_box->render(target);
	}

	if (_showDeath)
	{
		_death->render(target);
	}

	Scene::render(target);
}
