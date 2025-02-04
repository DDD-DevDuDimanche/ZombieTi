#include "pch.h"
#include "Window.h"

core::Window::Window(std::string name)
{
	// 1 - Search conf file or create it if not found

	// 2 - load the settings of the conf file

	// 3 - Create the windows and configure options
	_instance = sf::RenderWindow(
		sf::VideoMode({1280, 768}),
		name
	);
}

sf::RenderWindow& core::Window::getInstance()
{
	return _instance;
}
