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
    this->pos = {4.0f, 1.0f, 0.0f};
    this->texture = LoadTexture("./assets/knight.png");
    this->speed = 5.0f;

    this->size = {0.1f, 2.0f, 1.0f};

    this->bb.min = {this->pos.x - this->size.x / 2, this->pos.y - this->size.y / 2, this->pos.z - this->size.z / 2};
    this->bb.max = {this->pos.x + this->size.x / 2, this->pos.y + this->size.y / 2, this->pos.z + this->size.z / 2};

    this->stats = 1;
}

const Camera &PlayerController::get_camera() const
{
    return this->camera;
}

const Vector3 PlayerController::get_position() const
{
    return this->pos;
}

void PlayerController::render()
{
    // Render bullets
    weapon_controller.render();

    DrawBillboard(this->camera, this->texture, pos, 2.0f, WHITE);
    DrawBoundingBox(this->bb, BLUE);
}

void PlayerController::update()
{
    // Player pos: side-side
    float mouse_offset = (GetMousePosition().x / GetScreenWidth()) * 2.0f - 1.0f;

    pos.z = mouse_offset * 7.0f;

    if (pos.z < -4.0f)
        pos.z = -4.0f;
    if (pos.z > 4.0f)
        pos.z = 4.0f;

    // Player pos: forwards
    pos.x += speed * GetFrameTime();

    // Update bounding box position
    this->bb.min.x += speed * GetFrameTime();
    this->bb.max.x += speed * GetFrameTime();
    this->bb.min.z = this->pos.z - this->size.z / 2;
    this->bb.max.z = this->pos.z + this->size.z / 2;

    // Set camera relative to player
    camera.position.x = pos.x - distance_to_camera;
    camera.target.x = camera.position.x + 10.0f;

    // Fire shots
    weapon_controller.update(pos);
}

const BoundingBox &PlayerController::get_bounding_box() const
{
    return this->bb;
}

const int PlayerController::get_stats() const
{
    return this->stats;
}

void PlayerController::set_stats(int new_value)
{
    this->stats = new_value;
}

void PlayerController::update_stats(GateType gate_type, int gate_value)
{
    switch (gate_type)
    {
    case GateType::ADD:
        this->stats += gate_value;
        break;
    case GateType::SUBTRACT:
        this->stats -= gate_value;
        break;
    case GateType::MULTIPLY:
        this->stats *= gate_value;
        break;
    case GateType::DIVIDE:
        this->stats /= std::ceil(gate_value);
        break;

    default:
        return;
    }

    if (this->stats < 1)
    {
        this->stats = 1;
    }
}
