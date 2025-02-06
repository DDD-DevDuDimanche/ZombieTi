#pragma once
#ifndef WINDOW_H
#define WINDOW_H

namespace core
{
	class Window
	{
	public:
		Window(std::string name);
		~Window() {};

		sf::RenderWindow& getInstance();

	private:
		sf::RenderWindow _instance;
	};
}

#endif WINDOW_H