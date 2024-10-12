#include "WeaponController.hpp"

WeaponController::WeaponController(float projectile_interval)
{
    this->projectile_interval = projectile_interval;
    this->projectile_frametime_counter = 0.0f;
}

void WeaponController::update(Vector3 pos)
{
    this->projectile_frametime_counter += GetFrameTime();
    if (this->projectile_frametime_counter >= this->projectile_interval)
    {
        this->projectile_frametime_counter = 0.0f;

        // Fire
        projectiles.emplace_back(pos, 10.0f);
    }

    // Update shots
    for (auto it = projectiles.begin(); it != projectiles.end(); it++)
    {
        it->update();
        if (it->get_pos().x - pos.x > 20)
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

const std::vector<Projectile> &WeaponController::get_projectiles() const
{
    return this->projectiles;
}

std::vector<Projectile> &WeaponController::get_projectiles()
{
    return this->projectiles;
}

std::vector<Projectile>::iterator WeaponController::erase_projectile(std::vector<Projectile>::iterator it)
{
    return this->projectiles.erase(it);
}
