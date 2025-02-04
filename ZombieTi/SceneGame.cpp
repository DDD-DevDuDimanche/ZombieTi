#include "pch.h"
#include "SceneGame.h"

SceneGame::SceneGame(sf::RenderWindow* _window, std::stack<Scene*>* scenes) 
	: Scene(_window, scenes), _moneyText(_font), _hpText(_font), _bulletsText(_font)
{
	std::cout << "SceneGame::SceneGame::Creation..." << std::endl;
	_background = new sf::RectangleShape(sf::Vector2f(_windowReference->getSize().x, _windowReference->getSize().y));
	_background->setTexture(&TextureLoader::loadTexture("Assets/game_background.png"));
	std::cout << "SceneGame::SceneGame::Background Texture loaded" << std::endl;
	_map = new Map();
	_player = new Player(sf::Vector2f(Tile::TILE_SIZE * 9, Tile::TILE_SIZE * 5), _map);
	_showShop = false;
	_showBox = false;

	_money = 0;
	_moneyText.setCharacterSize(40);
	_moneyText.setFillColor(sf::Color(255, 255, 0, 255));
	_moneyText.setString(std::to_string(_money));
	_moneyText.setPosition({ Tile::TILE_SIZE + 10, _windowReference->getSize().y - Tile::TILE_SIZE });
	_moneyShape.setSize({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_moneyShape.setPosition({ 0, _windowReference->getSize().y - Tile::TILE_SIZE });
	_moneyShape.setTexture(&TextureLoader::loadTexture("Assets/icon_money.png"));
	std::cout << "SceneGame::SceneGame::Money Texture loaded" << std::endl;


	_hp = 30;
	_hpText.setCharacterSize(40);
	_hpText.setFillColor(sf::Color(255, 0, 0, 255));
	_hpText.setString(std::to_string(_hp));
	_hpText.setPosition({ Tile::TILE_SIZE * 5 + 10, _windowReference->getSize().y - Tile::TILE_SIZE });
	_hpShape.setSize({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_hpShape.setTexture(&TextureLoader::loadTexture("Assets/icon_hp.png"));
	_hpShape.setPosition({ Tile::TILE_SIZE * 4, _windowReference->getSize().y - Tile::TILE_SIZE });
	std::cout << "SceneGame::SceneGame::HP Texture loaded" << std::endl;

	_bullets = 10;
	_bulletsText.setCharacterSize(40);
	_bulletsText.setFillColor(sf::Color(255, 255, 255, 255));
	_bulletsText.setString(std::to_string(_bullets));
	_bulletsText.setPosition({ Tile::TILE_SIZE * 8 + 10, _windowReference->getSize().y - Tile::TILE_SIZE });
	_bulletsShape.setSize({ Tile::TILE_SIZE, Tile::TILE_SIZE });
	_bulletsShape.setTexture(&TextureLoader::loadTexture("Assets/icon_bullets.png"));
	_bulletsShape.setPosition({ Tile::TILE_SIZE * 7, _windowReference->getSize().y - Tile::TILE_SIZE });
	std::cout << "SceneGame::SceneGame::Bullets Texture loaded" << std::endl;

	_luck = 0;
	std::cout << "SceneGame::SceneGame::Creation done" << std::endl;

	_shop = new InterfaceShop(_windowReference, _font, &_moneyText, &_hpText, &_bulletsText, _luck);
	_box = new InterfaceBox(_windowReference, _font, &_moneyText, _luck);
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
	_player->update(dt, getKeyTimeDelay());

	if (!_showShop && !_showBox)
	{
		// Player interaction
		static bool lastInteraction = false;
		bool actualInteraction = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
		if (!lastInteraction && actualInteraction)
		{
			switch (_map->getTile(_player->getPosition())->getType())
			{
			case TileType::ZOMBIE:
				std::cout << "SceneGame::update::Interaction with Zombie Tile" << std::endl;
				_money += 5;
				_moneyText.setString(std::to_string(_money));
				_hp -= 2;
				_hpText.setString(std::to_string(_hp));
				_bullets--;
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
		_box->update(_mousePositionView);

		if (_shop->getButtons()["close"]->isPressed())
		{
			std::cout << "Close button" << std::endl;
			_showShop = false;
		}

		if (_box->getButtons()["close"]->isPressed())
		{
			std::cout << "Close button" << std::endl;
			_showBox = false;
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
	
	if (_showShop)
	{
		_shop->render(target);
	}

	if (_showBox)
	{
		_box->render(target);
	}

	Scene::render(target);
}
