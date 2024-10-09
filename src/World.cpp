#include "World.hpp"

World::World()
{
}

void World::update()
{
    player_controller.update();
}

void World::render()
{
    DrawGrid(100, 1.0f);
    DrawCube({0.0f, 0.5f, -5.0f}, 100.0f, 1.0f, 0.0f, GRAY);
    DrawCube({0.0f, 0.5f, 5.0f}, 100.0f, 1.0f, 0.0f, GRAY);
    DrawPlane({0.0f, 0.0f, 0.0f}, {100.0f, 10.0f}, DARKBROWN);
    player_controller.render();
}

const PlayerController &World::get_player() const
{
    return this->player_controller;
}
