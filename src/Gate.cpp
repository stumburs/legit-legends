#include "Gate.hpp"
#include "Text3D.hpp"
#include "rlgl.h"
#include <random>

Gate::Gate(Vector3 pos, Color color, GateType type, int value)
{
    this->pos = pos;
    this->color = color;
    this->type = type;
    this->value = value;

    this->size = {0.1f, 4.0f, 5.0f};
    this->bb.min = {this->pos.x - this->size.x / 2, this->pos.y - this->size.y / 2, this->pos.z - this->size.z / 2};
    this->bb.max = {this->pos.x + this->size.x / 2, this->pos.y + this->size.y / 2, this->pos.z + this->size.z / 2};
}

void Gate::randomize()
{
    this->type = this->get_random_type();
    this->value = this->get_random_value();
    this->color = this->get_type_color();
}

void Gate::update()
{
}

void Gate::render()
{
    rlPushMatrix();
    // rlDisableDepthTest();
    DrawCubeV({this->pos.x, this->pos.y, this->pos.z}, this->size, this->color);
    // DrawBoundingBox(this->bb, BLUE);
    // rlEnableDepthMask();

    // Render 3D text
    rlTranslatef(this->pos.x - this->size.x, this->pos.y + 1.0f, this->pos.z - Text3D::MeasureText3D(GetFontDefault(), get_formatted_value().c_str(), 10.0f, 1.0f, 0.0f).x / 2);
    rlRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    rlRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    Text3D::DrawText3D(GetFontDefault(), get_formatted_value().c_str(), {0.0f, 0.0f, 0.0f}, 10.0f, 1.0f, 0.0f, false, BLACK);
    rlPopMatrix();
}

const Vector3 Gate::get_pos() const
{
    return this->pos;
}

const std::string Gate::get_formatted_value() const
{
    switch (this->type)
    {
    case GateType::ADD:
        return "+" + std::to_string(this->value);
        break;
    case GateType::SUBTRACT:
        return "-" + std::to_string(this->value);
        break;
    case GateType::MULTIPLY:
        return "×" + std::to_string(this->value);
        break;
    case GateType::DIVIDE:
        return "÷" + std::to_string(this->value);
        break;

    default:
        return "Unknown";
    }
}

const BoundingBox &Gate::get_bounding_box() const
{
    return this->bb;
}

const GateType Gate::get_type() const
{
    return this->type;
}

const int Gate::get_value() const
{
    return this->value;
}

const Color Gate::get_type_color() const
{
    switch (this->type)
    {
    case GateType::ADD:
        return {0, 255, 0, 60};
        break;
    case GateType::SUBTRACT:
        return {255, 0, 0, 60};
        break;
    case GateType::MULTIPLY:
        return {180, 160, 20, 60};
        break;
    case GateType::DIVIDE:
        return {30, 30, 0, 60};
        break;

    default:
        return LIME;
    }
}

const int Gate::get_random_value() const
{
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 6);
    return distrib(gen);
}

void Gate::increment_value(int by)
{
    this->value += by;
}

const GateType Gate::get_random_type() const
{
    std::vector<GateType> types = {GateType::ADD, GateType::SUBTRACT, GateType::MULTIPLY, GateType::DIVIDE};
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, types.size() - 1);
    return types[distrib(gen)];
}
