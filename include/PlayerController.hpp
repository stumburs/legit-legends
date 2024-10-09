#pragma once
#include "raylib.h"
#include <vector>
#include "WeaponController.hpp"

class PlayerController
{
public:
    PlayerController();
    const Camera &get_camera() const;
    const Vector3 get_position() const;
    void render();
    void update();

private:
    Camera camera;
    Vector3 player_pos;
    Texture2D texture;
    float speed;
    float distance_to_camera;

    WeaponController weapon_controller;
};