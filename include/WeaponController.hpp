#pragma once
#include <vector>
#include "raylib.h"
#include "Projectile.hpp"

class WeaponController
{
public:
    WeaponController(float projectile_interval);
    void update(Vector3 pos);
    void render();

private:
    std::vector<Projectile> projectiles;
    float projectile_interval; // seconds
    float projectile_frametime_counter;
};