#include "World.hpp"
#include <iostream>

World::World()
{
    this->gate_interval = 40.0f;
}

void World::update()
{
    player_controller.update();

    if (gates.empty())
    {
        Vector3 gate_pos = player_controller.get_position();
        gate_pos.x += gate_interval;
        gate_pos.z = -2.5f;
        gates.emplace_back(gate_pos, Color{0, 255, 0, 60});

        gate_pos.z = 2.5f;
        gates.emplace_back(gate_pos, Color{255, 0, 0, 60});
    }

    // Update gates
    for (auto it = gates.begin(); it != gates.end();)
    {
        it->update();

        // Remove gates behind player
        if (it->get_pos().x < player_controller.get_position().x)
        {
            it = gates.erase(it);
        }
        else
        {
            ++it;
        }
    }

    while (gates.back().get_pos().x - player_controller.get_position().x < 100)
    {
        Vector3 new_gate_pos = gates.back().get_pos();
        new_gate_pos.x += gate_interval;
        new_gate_pos.z = -2.5f;
        gates.emplace_back(new_gate_pos, Color{0, 255, 0, 60});

        new_gate_pos.z = 2.5f;
        gates.emplace_back(new_gate_pos, Color{255, 0, 0, 60});
    }

    std::cout << gates.size() << std::endl;
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

    for (auto &gate : gates)
    {
        gate.render();
    }

    player_controller.render();
}

const PlayerController &World::get_player() const
{
    return this->player_controller;
}
