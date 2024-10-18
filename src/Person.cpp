#include "Person.hpp"

Person::Person(Vector3 pos, Vector3 size, float speed, const char *texture_path)
{
    this->pos = pos;
    this->size = size;
    this->speed = speed;

    this->bb.min = {this->pos.x - this->size.x / 2, this->pos.y - this->size.y / 2, this->pos.z - this->size.z / 2};
    this->bb.max = {this->pos.x + this->size.x / 2, this->pos.y + this->size.y / 2, this->pos.z + this->size.z / 2};

    this->texture = LoadTexture(texture_path);
}

void Person::update()
{
    this->pos.x += this->speed * GetFrameTime();

    this->bb.min.x = this->pos.x - this->size.x / 2;
    this->bb.max.x = this->pos.x + this->size.x / 2;
    this->bb.min.z = this->pos.z - this->size.z / 2;
    this->bb.max.z = this->pos.z + this->size.z / 2;
}

void Person::render(const Camera3D &camera)
{
    DrawBillboard(camera, this->texture, this->pos, 2.0f, WHITE);
    DrawBoundingBox(this->bb, BLUE);
}

const Vector3 Person::get_position() const
{
    return this->pos;
}

const Texture2D &Person::get_texture() const
{
    return this->texture;
}

const BoundingBox &Person::get_bounding_box() const
{
    return this->bb;
}

void Person::set_pos(Vector3 new_pos)
{
    this->pos = new_pos;
}

void Person::set_pos(float x, float y, float z)
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
}

void Person::set_pos_z(float z)
{
    this->pos.z = z;
}
