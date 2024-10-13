#include "PlayerController.hpp"
#include "raymath.h"
#include <iostream>

PlayerController::PlayerController() : weapon_controller(WeaponController(1.0f)), person(Person(Vector3{4.0f, 1.0f, 0.0f}, Vector3{0.1f, 2.0f, 1.0f}, 5.0f, "./assets/knight.png"))
{
    // Camera
    this->camera.fovy = 90.0f;
    this->camera.position = {0.0f, 5.0f, 0.0f};
    this->camera.projection = CameraProjection::CAMERA_PERSPECTIVE;
    this->camera.target = {10.0f, 0.0f, 0.0f};
    this->camera.up = {0.0f, 1.0f, 0.0f};

    this->distance_to_camera = 4.0f;

    this->stats = 1;
}

const Camera &PlayerController::get_camera() const
{
    return this->camera;
}

const Vector3 PlayerController::get_position() const
{
    return this->person.get_position();
}

void PlayerController::render()
{
    // Render bullets
    weapon_controller.render();

    DrawBillboard(this->camera, this->person.get_texture(), this->person.get_position(), 2.0f, WHITE);
    DrawBoundingBox(this->person.get_bounding_box(), BLUE);
}

void PlayerController::update()
{
    // Player pos: side-side
    float mouse_offset = (GetMousePosition().x / GetScreenWidth()) * 2.0f - 1.0f;

    person.set_pos({person.get_position().x, person.get_position().y, mouse_offset * 7.0f});

    if (person.get_position().z < -4.0f)
        person.set_pos_z(-4.0f);
    if (person.get_position().z > 4.0f)
        person.set_pos_z(4.0f);

    // Player pos: forwards
    person.update();

    // Set camera relative to player
    camera.position.x = person.get_position().x - distance_to_camera;
    camera.target.x = camera.position.x + 10.0f;

    // Fire shots
    weapon_controller.update(person.get_position());
}

const BoundingBox &PlayerController::get_bounding_box() const
{
    return this->person.get_bounding_box();
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

const WeaponController &PlayerController::get_weapon_controller() const
{
    return this->weapon_controller;
}

WeaponController &PlayerController::get_weapon_controller()
{
    return this->weapon_controller;
}
