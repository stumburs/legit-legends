#pragma once
#include "raylib.h"

class Projectile
{
public:
    Projectile(Vector3 pos, float speed);
    void update();
    void render() const;

    const Vector3 get_pos() const;
    const BoundingBox get_bounding_box() const;

private:
    Vector3 pos;
    float speed;
    Vector3 size;
    BoundingBox bb;
};