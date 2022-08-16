#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Vector2.hpp"

class Point {
public:
    Point(const Vector2& pos = {0.f, 0.f}, const sf::Color& color = sf::Color::White);
    Point(const Vector2& pos, const sf::Color& color, const Vector2& center);
    void setPosition(const Vector2& pos);
    [[nodiscard]] sf::Color getColor();
    [[nodiscard]] Vector2 getAxisX();
    [[nodiscard]] Vector2 getAxisY();
    [[nodiscard]] virtual std::vector<Vector2> getPosition();
    [[nodiscard]] virtual std::vector<Vector2> getSourcePosition();
    virtual void rotate(float angle);
    virtual void draw(sf::RenderWindow& window);
protected:
    Vector2 pos;
    Vector2 center;
    Vector2 axisX;
    Vector2 axisY;
    sf::Color color;
private:
    sf::CircleShape _point = sf::CircleShape(1.f);
};

#endif