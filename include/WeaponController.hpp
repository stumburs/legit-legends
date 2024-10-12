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

    const std::vector<Projectile> &get_projectiles() const;
    std::vector<Projectile> &get_projectiles();
    std::vector<Projectile>::iterator erase_projectile(std::vector<Projectile>::iterator it);

private:
    std::vector<Projectile> projectiles;
    float projectile_interval; // seconds
    float projectile_frametime_counter;
};