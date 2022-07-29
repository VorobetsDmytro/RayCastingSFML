#include "Raycast.hpp"

void Raycast::start(){
	buildMap();
	while (_window->isOpen()){
		_window->clear();
		update();
		_window->display();
	}
}

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
}

void Raycast::drawWalls(){
	_ray->setColor(sf::Color::Green);
	for(auto wall : _walls){
		_ray->setPosition(
			sf::Vector2f(wall.x1, wall.y1),
			sf::Vector2f(wall.x2, wall.y2)
		);
		_window->draw(_ray->getSource());
	}
}

void Raycast::drawWall3d(const Vector2& start, const Vector2& end, int wallPosX, float angle) {
	const int width = _wndWidth / 2;
	float length = Vector2::length(start, end);
	float wallWidth = width / (_fov * _density);
	float wallHeight = _wndHeight * 50.f / (length * cos(Vector2::degToRad(angle)));
	int alpha = (255 / length) * 160;
	alpha = alpha > 255 ? 255
		  : alpha < 0 ? 0
		  : alpha;
	_wall3D->setFillColor(sf::Color(alpha, 0, 0, 255));
	_wall3D->setSize({wallWidth, wallHeight});
	float x = (wallPosX  * wallWidth) + width;
	float y = (_wndHeight - wallHeight) / 2;
	_wall3D->setPosition({x, y});
	_window->draw(*_wall3D.get());
}

void Raycast::drawRays(){
	_ray->setColor(sf::Color::White);
	const int FOV = _fov / 2;
	Mouse* mouse = _mouse.get();
	float mouseX = mouse->getPosition().x;
	float mouseY = mouse->getPosition().y;
	int wallPosX = 0;
	for (float angle = FOV; angle >= -FOV; angle -= 1.f / _density) {
		Vector2 rayCoord = Vector2::rotate(angle + _direction, _castDistance);
		float rayEndX = rayCoord.x + mouseX;
		float rayEndY = rayCoord.y + mouseY;
		bool hit = false;
		for(auto wall : _walls){
			Vector2 inetsectCoord = Vector2::intersection({mouseX, mouseY}, {rayEndX, rayEndY}, {wall.x1, wall.y1}, {wall.x2, wall.y2});
			if(inetsectCoord.x != FLT_MAX && inetsectCoord.y != FLT_MAX){
				rayEndX = inetsectCoord.x;
				rayEndY = inetsectCoord.y;
				hit = true;
			}
		}
		_ray->setPosition(
			sf::Vector2f(mouseX, mouseY),
			sf::Vector2f(rayEndX, rayEndY)
		);
		if(hit)
			drawWall3d({mouseX + 600.f, mouseY}, {rayEndX + 600.f, rayEndY}, wallPosX, angle);
		if(mouseX <= _wndWidth / 2 + 1.f && rayEndX <= _wndWidth / 2 + 1.f)
			_window->draw(_ray->getSource());
		++wallPosX;
	}
}

void Raycast::buildRectangle(const Vector2& pos, const Vector2& size) {
	_walls.push_back(Wall(pos.x, pos.y, size.x + pos.x, pos.y));
	_walls.push_back(Wall(size.x + pos.x, pos.y, size.x + pos.x, size.y + pos.y));
	_walls.push_back(Wall(size.x + pos.x, size.y + pos.y, pos.x, size.y + pos.y));
	_walls.push_back(Wall(pos.x, size.y + pos.y, pos.x, pos.y));
}

void Raycast::buildMap(){
	const int width = _wndWidth / 2;
	const int height = _wndHeight / 2;
	buildRectangle({0.f, 0.f}, {(float)width, (float)_wndHeight});
	buildRectangle({(float)width / 2, (float)height}, {100.f, 100.f});
	buildRectangle({(float)width / 3, (float)height / 2}, {50.f, 50.f});
	buildRectangle({(float)width / 4, (float)height / 1.1f}, {75.f, 30.f});
	buildRectangle({(float)width / 1.3f, (float)height / 4}, {35.f, 125.f});
	buildRectangle({(float)width / 4, (float)height * 1.5f}, {125.f, 35.f});
}

void Raycast::setOption(RaycastSettings option, float value){
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