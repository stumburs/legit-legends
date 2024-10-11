#pragma once
#include "raylib.h"
#include <string>

enum class GateType
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
};

class Gate
{
public:
    Gate(Vector3 pos, Color color, GateType type, int value);
    void update();
    void render();
    const Vector3 get_pos() const;
    const std::string get_formatted_value() const;

private:
    Vector3 pos;
    Color color;
    GateType type;
    int value;
};