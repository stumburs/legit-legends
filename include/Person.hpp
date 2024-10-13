#pragma once
#include "raylib.h"

class Person
{
public:
    Person(Vector3 pos, Vector3 size, float speed, const char *texture_path);
    void update();
    void render();
    const Vector3 get_position() const;
    const Texture2D &get_texture() const;
    const BoundingBox &get_bounding_box() const;
    void set_pos(Vector3 new_pos);
    void set_pos(float x, float y, float z);
    void set_pos_z(float z);

private:
    Vector3 pos;

    Vector3 size;
    BoundingBox bb;

    float speed;

    // TODO: Rework texture storage
    Texture2D texture;
};