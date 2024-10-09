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
    // DrawGrid(200, 1.0f);

    const float chunk_length = 100.0f;

    int current_chunk_index = static_cast<int>(player_controller.get_position().x / chunk_length);

    for (int i = 0; i < 3; i++) // Render 3 'chunks' of ground in front
    {
        float chunk_x_pos = (current_chunk_index + i) * chunk_length;

        DrawCube({chunk_x_pos, 0.5f, -5.0f}, chunk_length, 1.0f, 0.0f, GRAY);
        DrawCube({chunk_x_pos, 0.5f, 5.0f}, chunk_length, 1.0f, 0.0f, GRAY);
        DrawPlane({chunk_x_pos, 0.0f, 0.0f}, {chunk_length, 10.0f}, DARKBROWN);
    }
    player_controller.render();
}

const PlayerController &World::get_player() const
{
    return this->player_controller;
}
