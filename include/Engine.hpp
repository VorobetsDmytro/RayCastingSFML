#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Mouse.hpp"

class Engine {
public:
	Engine(int width, int height, std::string title, sf::Uint32 style)
		: window(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, style)), 
		  wndWidth(window->getSize().x), wndHeight(window->getSize().y){}
	virtual void start();
	virtual void showFPS();
protected:
	virtual void update(){}
	virtual void buildMap(){}
	virtual void drawEnvironments();
	sf::Color farEffect(const sf::Color& color, float distance, int brightness);
	sf::Color brightColor(const sf::Color& color, int brightness);
	void calculateFPS();
	sf::Event event;
	const std::shared_ptr<sf::RenderWindow> window;
	const std::shared_ptr<Mouse> mouse = std::make_shared<Mouse>(window.get());
	const int wndWidth;
	const int wndHeight;
	float fps;
	float deltaTime;
	sf::Clock clock;
	sf::Time preTime;
	sf::Time curTime;
};

#endif