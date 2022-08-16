#include "Raycast.hpp"
#include "Rectangle.hpp"

void Raycast::update() {
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
            window->close();
		if (event.type == sf::Event::MouseWheelMoved)
			_direction = (_direction + (event.mouseWheel.delta * 10)) % 360 % -360;
	}
	drawEnvironments();
	drawWalls();
	drawRays();
	showFPS();

	//The rotated rectangle
	float speed = 75.f * deltaTime;
	_walls[1]->rotate(speed);
}

void Raycast::drawWalls() {
	for(auto wall : _walls)
		wall->draw(*window.get());
}

void Raycast::drawWall3d(const Vector2& rayStartPos, const Vector2& rayHitPos, int wallPosX, const sf::Color& wallColor, float angle) {
	const int halfWidth = wndWidth / 2;
	float distance = Vector2::length(rayStartPos, rayHitPos);
	float wallWidth = halfWidth / (_fov * _density);
	float wallHeight = wndHeight * 50.f / (distance * cos(Vector2::degToRad(angle)));
	sf::Color corWallColor = farEffect(wallColor, distance, 160);
	_wall3D->setFillColor(sf::Color(corWallColor.r, corWallColor.g, corWallColor.b, corWallColor.a));
	_wall3D->setSize({wallWidth, wallHeight});
	float x = (wallPosX  * wallWidth) + halfWidth;
	float y = (wndHeight - wallHeight) / 2;
	_wall3D->setPosition({x, y});
	window->draw(*_wall3D.get());
}

void Raycast::drawRays() {
	const int FOV = _fov / 2;
	float mouseX = mouse->getPosition().x;
	float mouseY = mouse->getPosition().y;
	int wallPosX = 0;
	for (float angle = FOV; angle >= -FOV; angle -= 1.f / _density) {
		Vector2 rayEndPos = Vector2::rotate({mouseX, mouseY}, angle + _direction, _castDistance);
		bool hit = false;
		int vertWallDarkness = 0;
		sf::Color wallColor(0, 0, 0);
		for(auto wall : _walls){
			Vector2 intersectCoord = wall->intersection({mouseX, mouseY}, {rayEndPos.x, rayEndPos.y}, vertWallDarkness);
			if(intersectCoord.x != FLT_MAX && intersectCoord.y != FLT_MAX){
				rayEndPos.x = intersectCoord.x;
				rayEndPos.y = intersectCoord.y;
				hit = true;
				wallColor = wall->getColor();
			}
		}
		_ray->setPosition(
			sf::Vector2f(mouseX, mouseY),
			sf::Vector2f(rayEndPos.x, rayEndPos.y)
		);
		if(hit){
			sf::Color wall3DColor = brightColor(wallColor, vertWallDarkness);
			drawWall3d({mouseX, mouseY}, {rayEndPos.x, rayEndPos.y}, wallPosX, wall3DColor, angle);
		}
		const int halfWidth = wndWidth / 2;
		if(mouseX <= halfWidth + 1.f && rayEndPos.x <= halfWidth + 1.f)
			window->draw(_ray->getSource());
		++wallPosX;
	}
}

void Raycast::buildMap() {
	const int halfWidth = wndWidth / 2;
	const int halfHeight = wndHeight / 2;
	_walls.push_back(new Rectangle({0.f, 0.f}, {(float)halfWidth, (float)wndHeight}, sf::Color::Red));
	_walls.push_back(new Rectangle({(float)halfWidth / 2, (float)halfHeight}, {100.f, 100.f}, sf::Color(244, 252, 3)));
	_walls.push_back(new Rectangle({(float)halfWidth / 3, (float)halfHeight / 2}, {50.f, 50.f}, sf::Color(252, 186, 3)));
	_walls.push_back(new Rectangle({(float)halfWidth / 4, (float)halfHeight / 1.1f}, {75.f, 30.f}, sf::Color(252, 3, 244)));
	_walls.push_back(new Rectangle({(float)halfWidth / 1.3f, (float)halfHeight / 4}, {35.f, 125.f}, sf::Color(3, 7, 252)));
	_walls.push_back(new Rectangle({(float)halfWidth / 4, (float)halfHeight * 1.5f}, {125.f, 35.f}, sf::Color(3, 252, 252)));
	_walls.push_back(new Line({100, 100}, {180, 100}, sf::Color::Green));
}

void Raycast::setOption(RaycastSettings option, float value) {
	switch (option) {
		case RaycastSettings::FOV:
			_fov = value <= 0.f ? 1.f
				 : value > 360.f ? 360.f
				 : value;
			break;
		case RaycastSettings::CAST_DISTANCE:
			_castDistance = value <= 0.f ? 1.f
						  : value;
			break;
		case RaycastSettings::DENSITY:
			_density = value <= 0.f ? 1.f
					 : value;
			break;
		case RaycastSettings::FPS_LIMIT:
			window->setFramerateLimit(value < 0.f ? 0 : (int)value);
			break;
		default:
			break;
	}
}