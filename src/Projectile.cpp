#include "Projectile.hpp"
#include <vector>

Projectile::Projectile(Vector3 pos, float speed)
{
    this->pos = pos;
    this->speed = speed;
    this->size = {0.2f, 0.2f, 0.2f};
    this->bb.min = {this->pos.x - this->size.x / 2, this->pos.y - this->size.y / 2, this->pos.z - this->size.z / 2};
    this->bb.max = {this->pos.x + this->size.x / 2, this->pos.y + this->size.y / 2, this->pos.z + this->size.z / 2};
}

void Projectile::update()
{
    this->pos.x += this->speed * GetFrameTime();
    this->bb.min.x += this->speed * GetFrameTime();
    this->bb.max.x += this->speed * GetFrameTime();
    this->bb.min.z = this->pos.z - this->size.z / 2;
    this->bb.max.z = this->pos.z + this->size.z / 2;
}

void Projectile::render() const
{
    DrawCubeV(this->pos, {0.2f, 0.2f, 0.2f}, YELLOW);
    DrawBoundingBox(this->bb, BLUE);
}

const Vector3 Projectile::get_pos() const
{
    return this->pos;
}

const BoundingBox Projectile::get_bounding_box() const
{
    return this->bb;
}