#ifndef RAYCAST_HPP
#define RAYCAST_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Engine.hpp"
#include "Ray.hpp"
#include "Vector2.hpp"
#include "float.h"

enum RaycastSettings {
	FOV,
	CAST_DISTANCE,
	DENSITY,
	FPS_LIMIT,
	WALL3D_COLOR
};

class Raycast final: public Engine {
public:
	Raycast(int width = 800, int height = 600, std::string title = "The Worst Engine", sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close)
		: Engine(width, height, title, style), _fov(90.f), _castDistance(200.f), _density(1.f), _direction(90), _ray(std::make_unique<Ray>()),
		_wall3D(std::make_unique<sf::RectangleShape>()), _wall3DColor(std::make_unique<sf::Color>()) {}
	void setOption(RaycastSettings option, float value);
	void setOption(RaycastSettings option, sf::Color value);
private:
	void update() override;
	void buildMap() override;
	void drawWalls();
	void drawRays();
	void drawWall3d(const Vector2& rayStartPos, const Vector2& rayHitPos, int wallPosX, const sf::Color& wallColor, float angle);
	float _fov;
	float _castDistance;
	float _density;
	int _direction;
	std::unique_ptr<Ray> _ray;
	std::unique_ptr<sf::RectangleShape> _wall3D;
	std::unique_ptr<sf::Color> _wall3DColor;
};

#endif