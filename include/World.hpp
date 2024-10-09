#pragma once
#include <PlayerController.hpp>
#include "Gate.hpp"

class World
{
public:
    World();
    void update();
    void render();
    const PlayerController &get_player() const;

private:
    PlayerController player_controller;
    std::vector<Gate> gates;
    float gate_interval; // units (X)
};