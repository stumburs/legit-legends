#pragma once
#include "raylib.h"
#include <vector>

class PlayerController
{
public:
    PlayerController();
    const Camera &get_camera() const;
    void render();
    void update();

private:
    Camera camera;
    Vector3 player_pos;
    Texture2D texture;
    float speed;
    float distance_to_camera;

    std::vector<Vector3> bullets;
    float bullet_interval; // seconds
    float bullet_frametime_counter;
    float bullet_speed;
};