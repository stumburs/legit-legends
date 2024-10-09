#include "WeaponController.hpp"

WeaponController::WeaponController(float projectile_interval)
{
    this->projectile_interval = projectile_interval;
    this->projectile_frametime_counter = 0.0f;
}

void WeaponController::update(Vector3 player_pos)
{
    this->projectile_frametime_counter += GetFrameTime();
    if (this->projectile_frametime_counter >= this->projectile_interval)
    {
        this->projectile_frametime_counter = 0.0f;

        // Fire
        projectiles.emplace_back(player_pos, 5.0f);
    }

    // Update shots
    for (auto it = projectiles.begin(); it != projectiles.end(); it++)
    {
        it->update();
        if (it->get_pos().x - player_pos.x > 20)
        {
            it = projectiles.erase(it);
        }
    }
}

void WeaponController::render()
{
    for (const auto &projectile : this->projectiles)
    {
        projectile.render();
    }
}
