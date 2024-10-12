#pragma once
#include "raylib.h"
#include <string>

enum class GateType
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    END,
};

class Gate
{
public:
    Gate(Vector3 pos, Color color, GateType type, int value);
    void randomize();
    void update();
    void render();
    const Vector3 get_pos() const;
    const std::string get_formatted_value() const;
    const BoundingBox &get_bounding_box() const;
    const GateType get_type() const;
    const int get_value() const;
    const Color get_type_color() const;
    const GateType get_random_type() const;
    const int get_random_value() const;

private:
    Vector3 pos;
    Color color;
    GateType type;
    int value;
    BoundingBox bb;
    Vector3 size;
};