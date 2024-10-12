#include "World.hpp"
#include <iostream>

World::World()
{
    this->gate_interval = 20.0f;
}

void World::update()
{
    player_controller.update();

    // Initialize first gates
    if (gates.empty())
    {
        Vector3 gate_pos = player_controller.get_position();
        gate_pos.x += gate_interval;
        gate_pos.z = -2.5f;
        Gate gate(gate_pos, GREEN, GateType::ADD, 1);
        gate.randomize();
        gates.push_back(gate);

        gate_pos.z = 2.5f;
        gate = Gate(gate_pos, GREEN, GateType::ADD, 1);
        gate.randomize();
        gates.push_back(gate);
    }

    // Update gates
    for (auto it = gates.begin(); it != gates.end();)
    {
        it->update();

        // Update gate value when bullet hits
        auto &projectiles = player_controller.get_weapon_controller().get_projectiles();
        for (auto bullet_it = projectiles.begin(); bullet_it != projectiles.end();)
        {
            if (CheckCollisionBoxes(it->get_bounding_box(), bullet_it->get_bounding_box()))
            {
                it->increment_value();
                bullet_it = projectiles.erase(bullet_it);
            }
            else
            {
                ++bullet_it;
            }
        }

        // Remove gates behind player
        if (CheckCollisionBoxes(it->get_bounding_box(), player_controller.get_bounding_box())) // TODO: Make sure player can only pick up one gate at a time
        {
            player_controller.update_stats(it->get_type(), it->get_value());
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

        Gate gate(new_gate_pos, GREEN, GateType::ADD, 1);
        gate.randomize();
        gates.push_back(gate);

        new_gate_pos.z = 2.5f;

        gate = Gate(new_gate_pos, GREEN, GateType::ADD, 1);
        gate.randomize();
        gates.push_back(gate);
    }
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
