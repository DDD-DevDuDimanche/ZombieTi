#include "pch.h"
#include "SceneGame.h"

SceneGame::SceneGame(sf::RenderWindow* _window, std::stack<Scene*>* scenes) : Scene(_window, scenes)
{
	std::cout << "SceneGame::SceneGame::Creation..." << std::endl;
	_background = new sf::RectangleShape(sf::Vector2f(_windowReference->getSize().x, _windowReference->getSize().y));
	_background->setTexture(&TextureLoader::loadTexture("Assets/game_background.png"));
	std::cout << "SceneGame::SceneGame::Background Texture loaded" << std::endl;
	_map = new Map();
	_player = new Player(sf::Vector2f(Tile::TILE_SIZE * 9, Tile::TILE_SIZE * 5), _map);
	_hud = new InterfaceHUD(_windowReference, _font, _player);
	_shop = new InterfaceShop(_windowReference, _font, _player, _hud);
	_box = new InterfaceBox(_windowReference, _font, _player, _hud);
	_death = new InterfaceDeath(_windowReference, _font);
	_hud->isVisible();
	std::cout << "SceneGame::SceneGame::Creation done" << std::endl;
}

SceneGame::~SceneGame()
{
	std::cout << "SceneGame::~SceneGame::Unload..." << std::endl;
	delete _map;
	delete _player;
	delete _hud;
	delete _shop;
	delete _box;
	delete _death;
	std::cout << "SceneGame::~SceneGame::Unload done" << std::endl;
}

void SceneGame::update(float& dt)
{
	Scene::update(dt);

	if (!_shop->isVisible() && !_box->isVisible() && !_death->isVisible())
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
				if (_player->getBullets() > 0)
				{
					_player->addMoney(_player->getWeapon().getDamage());
					_player->addHp(-2);
					_player->addBullets(-1);
					_hud->refresh();
				}
				break;
			case TileType::BOX:
				std::cout << "SceneGame::update::Interaction with Box Tile" << std::endl;
				_box->open();
				break;
			case TileType::SHOP:
				std::cout << "SceneGame::update::Interaction with Shop Tile" << std::endl;
				_shop->open();
				break;
			default:
				std::cout << "SceneGame::update::Interaction with nothing" << std::endl;
			}
		}

		lastInteraction = actualInteraction;
	}

	if (_shop->isVisible())
	{
		_shop->update(_mousePositionView);
	}

	if (_box->isVisible())
	{
		_box->update(_mousePositionView);
	}

	if (_player->getHp() <= 0)
	{
		_death->open();
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
	
	if (_shop->isVisible())
	{
		_shop->render(target);
	}

	if (_box->isVisible())
	{
		_box->render(target);
	}

	if (_death->isVisible())
	{
		_death->render(target);
	}

	_hud->render(target);
	Scene::render(target);
}
