#include "Raycast.hpp"
#include <memory>

int main() {
	std::unique_ptr<Raycast> game = std::make_unique<Raycast>(1280, 720);
	game->setOption(RaycastSettings::FOV, 60.f);
	game->setOption(RaycastSettings::CAST_DISTANCE, 2000.f);
	game->setOption(RaycastSettings::DENSITY, 10.f);
	game->setOption(RaycastSettings::FPS_LIMIT, 120.f);
	game->setOption(RaycastSettings::WALL3D_COLOR, {217, 153, 59});
	game->start();
    return 0;
}