#ifndef LINE_HPP
#define LINE_HPP

#include "Point.hpp"

class Line: protected Point {
public:
    Line(const Vector2& pos = {0.f, 0.f}, const Vector2& pos2 = {0.f, 0.f}, const sf::Color& color = sf::Color::White);
    Line(const Vector2& pos, const Vector2& pos2, const sf::Color& color, const Vector2& center);
    void setPosition(const Vector2& pos, const Vector2& pos2);
    [[nodiscard]] std::vector<Vector2> getPosition() override;
    [[nodiscard]] std::vector<Vector2> getSourcePosition() override;
    void rotate(float angle) override;
    void draw(sf::RenderWindow& window) override;
    virtual Vector2 intersection(const Vector2& start, const Vector2& end, int& vertWallDarkness);
protected:
    Vector2 pos2;
private:
    sf::VertexArray _line = sf::VertexArray(sf::LinesStrip, 2);
};

#endif