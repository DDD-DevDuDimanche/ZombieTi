#include "pch.h"
#include "SceneMainMenu.h"

SceneMainMenu::SceneMainMenu(sf::RenderWindow* _window, std::stack<Scene*>* scenes) : Scene(_window, scenes)
{
	std::cout << "SceneMainMenu::SceneMainMenu::Creation..." << std::endl;
	_background = new sf::RectangleShape(sf::Vector2f(_windowReference->getSize().x, _windowReference->getSize().y));
	_background->setTexture(&TextureLoader::loadTexture("Assets/main_menu_background.png"));
	std::cout << "SceneGame::SceneGame::Background Texture loaded" << std::endl;
	_buttons["start"] = new Button({ 150, (float) _windowReference->getSize().y - 300 }, _font, "Start");
	_buttons["exit"] = new Button({ 150, (float) _windowReference->getSize().y - 200 }, _font, "Exit");
	std::cout << "SceneMainMenu::SceneMainMenu::Creation done" << std::endl;
}

SceneMainMenu::~SceneMainMenu()
{
	std::cout << "SceneMainMenu::~SceneMainMenu::Unload done" << std::endl;
}

void SceneMainMenu::update(float& dt)
{
	Scene::update(dt);

	if (_buttons["start"]->isPressed())
	{
		_scenesReference->push(new SceneGame(_windowReference, _scenesReference));
	}

	if (_buttons["exit"]->isPressed())
	{
		_closeSignal = true;
	}
}

void SceneMainMenu::render(sf::RenderTarget* target)
{
	target->draw(*_background);
	Scene::render(target);
}
