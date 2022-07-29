#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Mouse.hpp"
#include "Wall.hpp"

class Engine {
public:
	Engine(int width, int height, std::string title, sf::Uint32 style)
		: _window(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, style)), 
		  _wndWidth(_window->getSize().x), _wndHeight(_window->getSize().y){}
protected:
	virtual void start(){}
	virtual void update(){}
	virtual void buildMap(){}
	virtual void drawEnvironments();
	sf::Event _event;
	std::vector<Wall> _walls;
	const std::shared_ptr<sf::RenderWindow> _window;
	const std::shared_ptr<Mouse> _mouse = std::make_shared<Mouse>(_window.get());
	const int _wndWidth;
	const int _wndHeight;
};

#endif