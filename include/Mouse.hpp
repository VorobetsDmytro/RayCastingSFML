#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/Graphics.hpp>

class Mouse {
public:
	Mouse(sf::RenderWindow* window): _window(window){}
	[[nodiscard]] sf::Vector2i getPosition(){
		return {
			sf::Mouse::getPosition(*_window).x,
			sf::Mouse::getPosition(*_window).y
		};
	}
private:
	sf::RenderWindow* _window;
};

#endif