#pragma once
#include "raylib.h"

// Source: https://www.raylib.com/examples/text/loader.html?name=text_draw_3d

namespace Text3D
{
    // Draw a codepoint in 3D space
    void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);
    // Draw a 2D text in 3D space
    void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);
    // Measure a text in 3D. For some reason `MeasureTextEx()` just doesn't seem to work so i had to use this instead.
    Vector3 MeasureText3D(Font font, const char *text, float fontSize, float fontSpacing, float lineSpacing);
} // namespace Text3D
