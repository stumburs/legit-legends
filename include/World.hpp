#pragma once
#include <PlayerController.hpp>

class World
{
public:
    World();
    void update();
    void render();
    const PlayerController &get_player() const;

private:
    PlayerController player_controller;
};