#include "Engine.hpp"

void Engine::start(){
	preTime = clock.getElapsedTime();
	buildMap();
	while (window->isOpen()){
		window->clear();
		update();
		window->display();
		calculateFPS();
	}
}

void Engine::calculateFPS() {
	curTime = clock.getElapsedTime();
	deltaTime = curTime.asSeconds() - preTime.asSeconds();
	fps = 1.0f / deltaTime;
	preTime = curTime;
}

void Engine::showFPS() {
	static sf::Clock showTimer;
	int curTimeSeconds = static_cast<int>(showTimer.getElapsedTime().asSeconds());
	if(curTimeSeconds >= 1){
		std::cout << "FPS = " << fps << std::endl;
		showTimer.restart();
	}
}

void Engine::drawEnvironments() {
    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color(52, 222, 235, 255));
	rectangle.setSize({wndWidth / 2.f, (float)wndHeight});
	rectangle.setPosition({wndWidth / 2.f, 0.f});
	window->draw(rectangle);
	sf::Vertex rectangleGradient[] = {
    	sf::Vertex({wndWidth / 2.f,  wndHeight / 2.f}, sf::Color(43, 43, 43, 255)),
    	sf::Vertex({(float)wndWidth, wndHeight / 2.f}, sf::Color(43, 43, 43, 255)),
		sf::Vertex({(float)wndWidth, (float)wndHeight}, sf::Color(143, 143, 143, 255)),
    	sf::Vertex({wndWidth / 2.f, (float)wndHeight}, sf::Color(143, 143, 143, 255)),
	};
	window->draw(rectangleGradient, 4, sf::PrimitiveType::Quads);
}

sf::Color Engine::farEffect(const sf::Color& color, float distance, int brightness){
	int red = (color.r / distance) * brightness;
	int green = (color.g / distance) * brightness;
	int blue = (color.b / distance) * brightness;
	red = red > color.r ? color.r
		  : red < 0 ? 0
		  : red;
	green = green > color.g ? color.g
		  : green < 0 ? 0
		  : green; 
	blue = blue > color.b ? color.b
		  : blue < 0 ? 0
		  : blue; 
	return { (sf::Uint8)red, (sf::Uint8)green, (sf::Uint8)blue, color.a };
}

sf::Color Engine::brightColor(const sf::Color& color, int brightness){
	int red = color.r + brightness;
	int green = color.g + brightness;
	int blue = color.b + brightness;
	red = red > 255 ? 255
		: red < 0 ? 0
		: red;
	green = green > 255 ? 255
		: green < 0 ? 0
		: green;
	blue = blue > 255 ? 255
		: blue < 0 ? 0
		: blue;
	return { (sf::Uint8)red, (sf::Uint8)green, (sf::Uint8)blue, color.a };
}