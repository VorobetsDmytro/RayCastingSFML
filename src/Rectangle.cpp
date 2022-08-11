#include "Rectangle.hpp"

Rectangle::Rectangle(const Vector2& pos, const Vector2& size, const sf::Color& color): Line(pos, size, color) {
    Vector2 point1 = Vector2({pos.x, pos.y});
    Vector2 point2 = Vector2({size.x + pos.x, pos.y});
    Vector2 point3 = Vector2({size.x + pos.x, size.y + pos.y});
    Vector2 point4 = Vector2({pos.x, size.y + pos.y});
    center = Vector2({(point1.x + point3.x) / 2, (point1.y + point3.y) / 2});
    _line[0].color = color;
    _line[1].color = color;
}

Rectangle::Rectangle(const Vector2& pos, const Vector2& size, const sf::Color& color, const Vector2& center): Line(pos, size, color, center) {
    Vector2 point1 = Vector2({pos.x, pos.y});
    Vector2 point2 = Vector2({size.x + pos.x, pos.y});
    Vector2 point3 = Vector2({size.x + pos.x, size.y + pos.y});
    Vector2 point4 = Vector2({pos.x, size.y + pos.y});
    _line[0].color = color;
    _line[1].color = color;
}

std::vector<Vector2> Rectangle::getPosition() {
    return {
        Vector2::position(Vector2({pos.x, pos.y}), axisX, axisY, center), 
        Vector2::position(Vector2({pos2.x + pos.x, pos.y}), axisX, axisY, center),
        Vector2::position(Vector2({pos2.x + pos.x, pos2.y + pos.y}), axisX, axisY, center),
        Vector2::position(Vector2({pos.x, pos2.y + pos.y}), axisX, axisY, center)
    };
}

std::vector<Vector2> Rectangle::getSourcePosition() {
    return {
        {pos.x, pos.y},
        {pos2.x + pos.x, pos.y},
        {pos2.x + pos.x, pos2.y + pos.y},
        {pos.x, pos2.y + pos.y}
    };
}

void Rectangle::setPosition(const Vector2& pos, const Vector2& pos2){
    this->pos = pos;
    this->pos2 = pos2;
}

void Rectangle::rotate(float angle) {
    axisX = Vector2::rotate(axisX, angle);
	axisY = Vector2::rotate(axisY, angle);
}

void Rectangle::draw(sf::RenderWindow& window){
    std::vector<Vector2> position = getPosition();
    for (int i = 1; i <= 4; ++i){
        _line[0].position = {position[i - 1].x, position[i - 1].y};
        _line[1].position = {position[i % 4].x, position[i % 4].y};
        window.draw(_line);
    }
}

Vector2 Rectangle::intersection(const Vector2& start, const Vector2& end, int& vertWallDarkness) {
    std::vector<Vector2> recPos = this->getPosition();
    std::vector<Vector2> recSourcePos = this->getSourcePosition();
    Vector2 rayEndPos(end.x, end.y);
    bool hit = false;
    for (int i = 1; i <= 4; ++i) {
        Vector2 intersectCoord = Vector2::intersection({start.x, start.y}, rayEndPos, {recPos[i - 1].x, recPos[i - 1].y}, {recPos[i % 4].x, recPos[i % 4].y});
        if(intersectCoord.x != FLT_MAX && intersectCoord.y != FLT_MAX){
			rayEndPos.x = intersectCoord.x;
			rayEndPos.y = intersectCoord.y;
            hit = true;
            vertWallDarkness = recSourcePos[i - 1].x == recSourcePos[i % 4].x ? -40 : 0;
        }
    }
    if(!hit)
        return {FLT_MAX, FLT_MAX};
    return rayEndPos;
}