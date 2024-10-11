#include "PlayerController.hpp"
#include "raymath.h"
#include <iostream>

PlayerController::PlayerController() : weapon_controller(WeaponController(1.0f))
{
    // Camera
    this->camera.fovy = 90.0f;
    this->camera.position = {0.0f, 5.0f, 0.0f};
    this->camera.projection = CameraProjection::CAMERA_PERSPECTIVE;
    this->camera.target = {10.0f, 0.0f, 0.0f};
    this->camera.up = {0.0f, 1.0f, 0.0f};

    this->distance_to_camera = 4.0f;

    // Player
    this->player_pos = {4.0f, 1.0f, 0.0f};
    this->texture = LoadTexture("./assets/knight.png");
    this->speed = 5.0f;
}

const Camera &PlayerController::get_camera() const
{
    return this->camera;
}

const Vector3 PlayerController::get_position() const
{
    return this->player_pos;
}

void PlayerController::render()
{
    // Render bullets
    weapon_controller.render();

    DrawBillboard(this->camera, this->texture, player_pos, 2.0f, WHITE);
    DrawCubeWires(player_pos, 0.0f, 2.0f, 1.0f, RED);
}

void PlayerController::update()
{
    // Player pos: side-side
    float mouse_offset = (GetMousePosition().x / GetScreenWidth()) * 2.0f - 1.0f;

    player_pos.z = mouse_offset * 7.0f;

    if (player_pos.z < -4.0f)
        player_pos.z = -4.0f;
    if (player_pos.z > 4.0f)
        player_pos.z = 4.0f;

    // Player pos: forwards
    player_pos.x += speed * GetFrameTime();

    // Set camera relative to player
    camera.position.x = player_pos.x - distance_to_camera;
    camera.target.x = camera.position.x + 10.0f;

    // Fire shots
    weapon_controller.update(player_pos);
}
