#pragma once
#include "raylib.h"
#include <vector>
#include "WeaponController.hpp"
#include "Gate.hpp"

class PlayerController
{
public:
    PlayerController();
    const Camera &get_camera() const;
    const Vector3 get_position() const;
    void render();
    void update();
    const BoundingBox &get_bounding_box() const;
    const int get_stats() const;
    void set_stats(int new_value);
    void update_stats(GateType gate_type, int gate_value);

private:
    Camera camera;
    Vector3 pos;
    Texture2D texture;
    float speed;
    float distance_to_camera;

    int stats;

    Vector3 size;
    BoundingBox bb;

    WeaponController weapon_controller;
};