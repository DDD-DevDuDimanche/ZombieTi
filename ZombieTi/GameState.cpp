#include "pch.h"
#include "GameState.h"

/* ==================================================
	Static Data
================================================== */
GameState* GameState::_instance = nullptr;
std::string GameState::NAME = "Zombie Ti";

/* ==================================================
	Public Side
================================================== */
GameState* GameState::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameState();
	}

	return _instance;
}

GameState::GameState()
{
	std::cout << "GameState::Loading start" << std::endl;

	_window = &(new core::Window(NAME))->getInstance();
	_dt = 0;
	_scenes.push(new SceneMainMenu(_window, &_scenes));

	std::cout << "GameState::Loading done" << std::endl;
}

GameState::~GameState()
{
	std::cout << "GameState::Clear data" << std::endl;
	
	delete _window;
	while (!_scenes.empty())
	{
		delete _scenes.top();
		_scenes.pop();
	}

	std::cout << "GameState::Closing" << std::endl;
}

void GameState::run()
{
	while (_window->isOpen())
	{
		update();
		render();
	}
}

/* ==================================================
	Private Side
================================================== */
void GameState::update()
{
	while (const std::optional event = _window->pollEvent())
	{
		// Windows Closing button event
		if (event->is<sf::Event::Closed>())
		{
			_window->close();
		}
	}

	// Clock
	_dt = _clock.restart().asSeconds();

	/*
		Update the last scene
		Destroy the last scene if close signal was received
		Close the game if there is no scene left
	*/
	if (!_scenes.empty())
	{
		_scenes.top()->update(_dt);

		if (_scenes.top()->getCloseSignal())
		{
			delete _scenes.top();
			_scenes.pop();
		}
	}
	else
	{
		_window->close();
	}
}

void GameState::render()
{
	_window->clear();

	// Render the last scene
	if (!_scenes.empty())
	{
		_scenes.top()->render(_window);
	}

	_window->display();
}
