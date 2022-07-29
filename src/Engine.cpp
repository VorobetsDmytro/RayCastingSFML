#include "Engine.hpp"

void Engine::drawEnvironments() {
    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color(52, 222, 235, 255));
	rectangle.setSize({_wndWidth / 2.f, (float)_wndHeight});
	rectangle.setPosition({_wndWidth / 2.f, 0.f});
	_window->draw(rectangle);
	sf::Vertex rectangleGradient[] = {
    	sf::Vertex({_wndWidth / 2.f,  _wndHeight / 2.f}, sf::Color(43, 43, 43, 255)),
    	sf::Vertex({(float)_wndWidth, _wndHeight / 2.f}, sf::Color(43, 43, 43, 255)),
		sf::Vertex({(float)_wndWidth, (float)_wndHeight}, sf::Color(143, 143, 143, 255)),
    	sf::Vertex({_wndWidth / 2.f, (float)_wndHeight}, sf::Color(143, 143, 143, 255)),
	};
	_window->draw(rectangleGradient, 4, sf::PrimitiveType::Quads);
}