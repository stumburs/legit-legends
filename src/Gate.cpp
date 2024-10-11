#include "Gate.hpp"
#include "Text3D.hpp"
#include "rlgl.h"

Gate::Gate(Vector3 pos, Color color, GateType type, int value)
{
    this->pos = pos;
    this->color = color;
    this->type = type;
    this->value = value;
}

void Gate::update()
{
}

void Gate::render()
{
    rlPushMatrix();
    // rlDisableDepthTest();
    DrawCube({this->pos.x, this->pos.y, this->pos.z}, 0.0f, 4.0f, 5.0f, this->color);
    // rlEnableDepthMask();

    // Render 3D text
    rlTranslatef(this->pos.x - 0.01f, this->pos.y + 1.0f, this->pos.z - Text3D::MeasureText3D(GetFontDefault(), get_formatted_value().c_str(), 10.0f, 1.0f, 0.0f).x / 2);
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
        return "*" + std::to_string(this->value);
        break;
    case GateType::DIVIDE:
        return "/" + std::to_string(this->value);
        break;

    default:
        return "Unknown";
    }
}
