#ifndef SCENE_H
#define SCENE_H

#include "Button.h"
#include "TextureLoader.h"

class Scene
{
public:
	Scene(sf::RenderWindow* _window, std::stack<Scene*>* scenes);
	virtual ~Scene();

	////////////////////////////////////////////////////////////
	/// Get the signal to destroy the scene
	////////////////////////////////////////////////////////////
	bool& getCloseSignal();

	////////////////////////////////////////////////////////////
	/// Get the end or not of the key time delay
	////////////////////////////////////////////////////////////
	bool getKeyTimeDelay();

	virtual void update(float& dt);
	virtual void render(sf::RenderTarget* target);

protected:
	////////////////////////////////////////////////////////////
	/// Reference of the main game window
	////////////////////////////////////////////////////////////
	sf::RenderWindow* _windowReference;

	////////////////////////////////////////////////////////////
	/// Reference of the game scenes
	////////////////////////////////////////////////////////////
	std::stack<Scene*>* _scenesReference;

	////////////////////////////////////////////////////////////
	/// Background of the actual scene
	////////////////////////////////////////////////////////////
	sf::RectangleShape* _background;

	////////////////////////////////////////////////////////////
	/// Signal to ask the game state to destroy the scene
	////////////////////////////////////////////////////////////
	bool _closeSignal;

	////////////////////////////////////////////////////////////
	/// Actual time of key pressed
	////////////////////////////////////////////////////////////
	float _keyTime;

	////////////////////////////////////////////////////////////
	/// Maximum time of key pressed to wait
	////////////////////////////////////////////////////////////
	float _keyTimeMax;

	////////////////////////////////////////////////////////////
	/// Font of the game
	////////////////////////////////////////////////////////////
	sf::Font _font;

	////////////////////////////////////////////////////////////
	/// Mouse position on the computer screen
	////////////////////////////////////////////////////////////
	sf::Vector2i _mousePositionScreen;

	////////////////////////////////////////////////////////////
	/// Mouse position on the game main window
	////////////////////////////////////////////////////////////
	sf::Vector2i _mousePositionWindow;

	////////////////////////////////////////////////////////////
	/// Mouse position on the game actual view
	////////////////////////////////////////////////////////////
	sf::Vector2f _mousePositionView;

	////////////////////////////////////////////////////////////
	/// Buttons of the scene
	////////////////////////////////////////////////////////////
	std::map<std::string, Button*> _buttons;
};

#endif SCENE_H