#include "Game.hpp"
#include "raylib.h"
#include "World.hpp"

void Game::run()
{
    SetConfigFlags(ConfigFlags::FLAG_MSAA_4X_HINT);
    InitWindow(1920, 1080, "Legit Legends");
    SetTargetFPS(144);

    World world;

    while (!WindowShouldClose())
    {
        // Update
        {
            world.update();
        }

        // Render
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            // 3D
            BeginMode3D(world.get_player().get_camera());
            {
                world.render();
            }
            EndMode3D();
            DrawFPS(20, 20);
        }
        EndDrawing();
    }

    CloseWindow();
}