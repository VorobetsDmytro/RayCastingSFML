#include "Line.hpp"

Line::Line(const Vector2& pos, const Vector2& pos2, const sf::Color& color): Point(pos, color), pos2(pos2) {
    center = Vector2({(pos.x + pos2.x) / 2, (pos.y + pos2.y) / 2});
    _line[0].color = color;
    _line[1].color = color;
}

Line::Line(const Vector2& pos, const Vector2& pos2, const sf::Color& color, const Vector2& center): Point(pos, color, center), pos2(pos2) {
    _line[0].color = color;
    _line[1].color = color;
}

std::vector<Vector2> Line::getPosition(){
	return {
        Vector2::position(pos, axisX, axisY, center), 
        Vector2::position(pos2, axisX, axisY, center)
    };
}

std::vector<Vector2> Line::getSourcePosition(){
	return {
        pos, 
        pos2
    };
}

void Line::setPosition(const Vector2& pos, const Vector2& pos2){
    this->pos = pos;
    this->pos2 = pos2;
}

void Line::rotate(float angle) {
    axisX = Vector2::rotate(axisX, angle);
	axisY = Vector2::rotate(axisY, angle);
}

void Line::draw(sf::RenderWindow& window){
    std::vector<Vector2> position = getPosition();
    for (int i = 0; i < 2; ++i)
        _line[i].position = {position[i].x, position[i].y};
    window.draw(_line);
}

Vector2 Line::intersection(const Vector2& start, const Vector2& end, int& vertWallDarkness) {
    std::vector<Vector2> linePos = this->getPosition();
    std::vector<Vector2> lineSourcePos = this->getSourcePosition();
    Vector2 res = Vector2::intersection({start.x, start.y}, {end.x, end.y}, {linePos[0].x, linePos[0].y}, {linePos[1].x, linePos[1].y});
    if(res.x != FLT_MAX && res.y != FLT_MAX)
        vertWallDarkness = lineSourcePos[0].x == lineSourcePos[1].x ? -40 : 0;
    return res;
}