#pragma once
#include "raylib.h"

class Gate
{
public:
    Gate(Vector3 pos, Color color);
    void update();
    void render();
    const Vector3 get_pos() const;

private:
    Vector3 pos;
    Color color;
};