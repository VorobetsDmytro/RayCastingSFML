#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Line.hpp"

class Rectangle final: public Line {
public:
    Rectangle(const Vector2& pos = {0.f, 0.f}, const Vector2& size = {0.f, 0.f}, const sf::Color& color = sf::Color::White);
    Rectangle(const Vector2& pos, const Vector2& size, const sf::Color& color, const Vector2& center);
    void setPosition(const Vector2& pos, const Vector2& pos2);
    [[nodiscard]] std::vector<Vector2> getPosition() override;
    [[nodiscard]] std::vector<Vector2> getSourcePosition() override;
    void rotate(float angle) override;
    void draw(sf::RenderWindow& window) override;
    [[nodiscard]] Vector2 intersection(const Vector2& start, const Vector2& end, int& vertWallDarkness) override;
private:
    sf::VertexArray _line = sf::VertexArray(sf::LinesStrip, 2);
};

#endif