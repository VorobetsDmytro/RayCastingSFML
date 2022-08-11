#include "Raycast.hpp"
#include "Rectangle.hpp"

void Raycast::update() {
	while (_window->pollEvent(_event)) {
		if (_event.type == sf::Event::Closed)
            _window->close();
		if (_event.type == sf::Event::MouseWheelMoved)
			_direction = (_direction + (_event.mouseWheel.delta * 10)) % 360 % -360;
	}
	drawEnvironments();
	drawWalls();
	drawRays();

	//The rotated rectangle
	_walls[1]->rotate(.5f);
}

void Raycast::drawWalls() {
	_ray->setColor(sf::Color::Green);
	for(auto wall : _walls)
		wall->draw(*_window.get());
}

void Raycast::drawWall3d(const Vector2& rayStartPos, const Vector2& rayHitPos, int wallPosX, const sf::Color& wallColor, float angle) {
	const int halfWidth = _wndWidth / 2;
	float distance = Vector2::length(rayStartPos, rayHitPos);
	float wallWidth = halfWidth / (_fov * _density);
	float wallHeight = _wndHeight * 50.f / (distance * cos(Vector2::degToRad(angle)));
	sf::Color corWallColor = farEffect(wallColor, distance, 160);
	_wall3D->setFillColor(sf::Color(corWallColor.r, corWallColor.g, corWallColor.b, corWallColor.a));
	_wall3D->setSize({wallWidth, wallHeight});
	float x = (wallPosX  * wallWidth) + halfWidth;
	float y = (_wndHeight - wallHeight) / 2;
	_wall3D->setPosition({x, y});
	_window->draw(*_wall3D.get());
}

void Raycast::drawRays() {
	_ray->setColor(sf::Color::White);
	const int FOV = _fov / 2;
	Mouse* mouse = _mouse.get();
	float mouseX = mouse->getPosition().x;
	float mouseY = mouse->getPosition().y;
	int wallPosX = 0;
	for (float angle = FOV; angle >= -FOV; angle -= 1.f / _density) {
		Vector2 rayEndPos = Vector2::rotate({mouseX, mouseY}, angle + _direction, _castDistance);
		bool hit = false;
		int vertWallDarkness = 0;
		for(auto wall : _walls){
			Vector2 intersectCoord = wall->intersection({mouseX, mouseY}, {rayEndPos.x, rayEndPos.y}, vertWallDarkness);
			if(intersectCoord.x != FLT_MAX && intersectCoord.y != FLT_MAX){
				rayEndPos.x = intersectCoord.x;
				rayEndPos.y = intersectCoord.y;
				hit = true;
			}
		}
		_ray->setPosition(
			sf::Vector2f(mouseX, mouseY),
			sf::Vector2f(rayEndPos.x, rayEndPos.y)
		);
		if(hit){
			sf::Color wall3DColor = brightColor(*_wall3DColor.get(), vertWallDarkness);
			drawWall3d({mouseX, mouseY}, {rayEndPos.x, rayEndPos.y}, wallPosX, wall3DColor, angle);
		}
		const int halfWidth = _wndWidth / 2;
		if(mouseX <= halfWidth + 1.f && rayEndPos.x <= halfWidth + 1.f)
			_window->draw(_ray->getSource());
		++wallPosX;
	}
}

void Raycast::buildMap() {
	const int halfWidth = _wndWidth / 2;
	const int halfHeight = _wndHeight / 2;
	_walls.push_back(new Rectangle({0.f, 0.f}, {(float)halfWidth, (float)_wndHeight}, sf::Color::Green));
	_walls.push_back(new Rectangle({(float)halfWidth / 2, (float)halfHeight}, {100.f, 100.f}, sf::Color::Green));
	_walls.push_back(new Rectangle({(float)halfWidth / 3, (float)halfHeight / 2}, {50.f, 50.f}, sf::Color::Green));
	_walls.push_back(new Rectangle({(float)halfWidth / 4, (float)halfHeight / 1.1f}, {75.f, 30.f}, sf::Color::Green));
	_walls.push_back(new Rectangle({(float)halfWidth / 1.3f, (float)halfHeight / 4}, {35.f, 125.f}, sf::Color::Green));
	_walls.push_back(new Rectangle({(float)halfWidth / 4, (float)halfHeight * 1.5f}, {125.f, 35.f}, sf::Color::Green));
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
			_window->setFramerateLimit(value < 0.f ? 0 : (int)value);
			break;
		default:
			break;
	}
}

void Raycast::setOption(RaycastSettings option, sf::Color value) {
	switch (option) {
		case RaycastSettings::WALL3D_COLOR:
			_wall3DColor = std::make_unique<sf::Color>(value);
			break;
		default:
			break;
	}
}