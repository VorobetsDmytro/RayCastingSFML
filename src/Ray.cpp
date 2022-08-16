#include "Ray.hpp"

Ray::Ray(const sf::Color& color): _ray(sf::VertexArray(sf::LinesStrip, 2)){
	setColor(color);
}

void Ray::setColor(const sf::Color& color){
	_ray[0].color = color;
	_ray[1].color = color;
}

void Ray::setPosition(const sf::Vector2f& start, const sf::Vector2f& end){
	_ray[0].position = start;
	_ray[1].position = end;
}