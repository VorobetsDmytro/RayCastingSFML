#ifndef RAY_HPP
#define RAY_HPP

#include <SFML/Graphics.hpp>

class Ray{
public:
	Ray(): _ray(sf::VertexArray(sf::LinesStrip, 2)){}
	void setColor(const sf::Color& color);
	void setPosition(const sf::Vector2f& start, const sf::Vector2f& end);
	[[nodiscard]] sf::VertexArray& getSource() { return _ray; }
private:
	sf::VertexArray _ray;
};

#endif