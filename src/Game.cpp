#include "Game.hpp"
#include "raylib.h"
#include "PlayerController.hpp"

void Game::run()
{
    SetConfigFlags(ConfigFlags::FLAG_MSAA_4X_HINT);
    InitWindow(1920, 1080, "Legit Legends");
    SetTargetFPS(144);

    PlayerController pc;

    while (!WindowShouldClose())
    {
        // Update
        {
            pc.update();
        }

        // Render
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            // 3D
            BeginMode3D(pc.get_camera());
            {
                DrawGrid(100, 1.0f);
                DrawCube({0.0f, 0.5f, -5.0f}, 100.0f, 1.0f, 0.0f, GRAY);
                DrawCube({0.0f, 0.5f, 5.0f}, 100.0f, 1.0f, 0.0f, GRAY);
                DrawPlane({0.0f, 0.0f, 0.0f}, {100.0f, 10.0f}, DARKBROWN);
                pc.render();
            }
            EndMode3D();
            DrawFPS(20, 20);
        }
        EndDrawing();
    }

    CloseWindow();
}