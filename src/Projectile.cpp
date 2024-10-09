#include "Projectile.hpp"

Projectile::Projectile(Vector3 pos, float speed)
{
    this->pos = pos;
    this->speed = speed;
}

void Projectile::update()
{
    this->pos.x += this->speed * GetFrameTime();
}

void Projectile::render() const
{
    DrawCubeV(this->pos, {0.2f, 0.2f, 0.2f}, YELLOW);
}

const Vector3 Projectile::get_pos() const
{
    return this->pos;
}
