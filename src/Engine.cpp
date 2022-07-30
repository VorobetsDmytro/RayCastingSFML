#include "Engine.hpp"

void Engine::start(){
	buildMap();
	while (_window->isOpen()){
		_window->clear();
		update();
		_window->display();
	}
}

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

sf::Color Engine::farEffect(const sf::Color& color, float distance, int brightness){
	int red = (color.r / distance) * brightness;
	int green = (color.g / distance) * brightness;
	int blue = (color.b / distance) * brightness;
	red = red > color.r ? color.r
		  : red < 0 ? 0
		  : red;
	green = green > color.g ? color.g
		  : green < 0 ? 0
		  : green; 
	blue = blue > color.b ? color.b
		  : blue < 0 ? 0
		  : blue; 
	return { (sf::Uint8)red, (sf::Uint8)green, (sf::Uint8)blue, color.a };
}

sf::Color Engine::brightColor(const sf::Color& color, int brightness){
	int red = color.r + brightness;
	int green = color.g + brightness;
	int blue = color.b + brightness;
	red = red > 255 ? 255
		: red < 0 ? 0
		: red;
	green = green > 255 ? 255
		: green < 0 ? 0
		: green;
	blue = blue > 255 ? 255
		: blue < 0 ? 0
		: blue;
	return { (sf::Uint8)red, (sf::Uint8)green, (sf::Uint8)blue, color.a };
}