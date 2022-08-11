#include "Point.hpp"

Point::Point(const Vector2& pos, const sf::Color& color): pos(pos), color(color), axisX({1.f, 0.f}), axisY({0.f, 1.f}){
    center = Vector2({pos.x, pos.y});
    _point.setFillColor(color);
}

Point::Point(const Vector2& pos, const sf::Color& color, const Vector2& center)
    : pos(pos), color(color), center(center), axisX({1.f, 0.f}), axisY({0.f, 1.f}){
    _point.setFillColor(color);
}

std::vector<Vector2> Point::getPosition(){
	return {Vector2::position(pos, axisX, axisY, center)};
}

std::vector<Vector2> Point::getSourcePosition(){
	return {pos};
}

void Point::setPosition(const Vector2& pos){
    this->pos = pos;
}

Vector2 Point::getAxisX() { return axisX; }
Vector2 Point::getAxisY() { return axisY; }

void Point::rotate(float angle) {
    axisX = Vector2::rotate(axisX, angle);
	axisY = Vector2::rotate(axisY, angle);
}

void Point::draw(sf::RenderWindow& window) {
    std::vector<Vector2> position = getPosition();
    _point.setPosition({position[0].x, position[0].y});
    window.draw(_point);
}