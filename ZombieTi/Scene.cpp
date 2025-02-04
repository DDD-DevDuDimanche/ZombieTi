#include "pch.h"
#include "Scene.h"

Scene::Scene(sf::RenderWindow* _window, std::stack<Scene*>* scenes)
{
    _windowReference = _window;
    _scenesReference = scenes;
    _background = NULL;
    _closeSignal = false;
    _keyTime = 0;
    _keyTimeMax = 30;

    if (!_font.openFromFile("Assets/Dosis-Light.ttf"))
    {
        std::cout << "Scene:Scene::Assets/Dosis-Light.ttf not found !" << std::endl;
        throw "Scene:Scene::Assets/Dosis-Light.ttf not found !";
    }
}

Scene::~Scene()
{
    delete _background;

    for (auto& index : _buttons) {
        delete index.second;
    }
}

bool& Scene::getCloseSignal()
{
    return _closeSignal;
}

bool Scene::getKeyTimeDelay()
{
    if (_keyTime >= _keyTimeMax)
    {
        _keyTime = 0;
        return true;
    }

    return false;
}

void Scene::update(float& dt)
{
    // Mouse position
    _mousePositionScreen = sf::Mouse::getPosition();
    _mousePositionWindow = sf::Mouse::getPosition(*_windowReference);
    _mousePositionView = _windowReference->mapPixelToCoords(sf::Mouse::getPosition(*_windowReference));

    // Buttons
    for (auto& index : _buttons) {
        index.second->update(_mousePositionView);
    }

    // Key Time delay
    if (_keyTime < _keyTimeMax)
    {
        _keyTime += 100 * dt;
    }
}

void Scene::render(sf::RenderTarget* target)
{
    for (auto& index : _buttons) {
        index.second->render(target);
    }

    // DEBUG
    sf::Text positionMouse = sf::Text(_font);
    positionMouse.setPosition({ _mousePositionView.x, _mousePositionView.y - 50 });
    positionMouse.setCharacterSize(30);
    std::stringstream ss;
    ss << _mousePositionView.x << " " << _mousePositionView.y;
    positionMouse.setString(ss.str());
    target->draw(positionMouse);
}
