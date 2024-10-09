#include "Gate.hpp"

Gate::Gate(Vector3 pos, Color color)
{
    this->pos = pos;
    this->color = color;
}

void Gate::update()
{
}

void Gate::render()
{
    DrawCube({this->pos.x, this->pos.y, this->pos.z}, 0.0f, 4.0f, 5.0f, this->color);
}

const Vector3 Gate::get_pos() const
{
    return this->pos;
}
