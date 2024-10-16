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

    this->stats = 1;

    people.emplace_back(Vector3{4.0f, 1.0f, 0.0f}, Vector3{0.1f, 2.0f, 1.0f}, 5.0f, "../assets/knight.png");
}

const Camera &PlayerController::get_camera() const
{
    return this->camera;
}

void PlayerController::render()
{
    // Render bullets
    weapon_controller.render();

    for (auto &person : people)
    {
        person.render(this->camera);
    }
}

void PlayerController::update()
{
    // Player pos: side-side
    float mouse_offset = (GetMousePosition().x / GetScreenWidth()) * 2.0f - 1.0f;

    // Update people
    for (auto &person : people)
    {
        person.set_pos({person.get_position().x, person.get_position().y, mouse_offset * 7.0f});

        if (person.get_position().z < -4.0f)
            person.set_pos_z(-4.0f);
        if (person.get_position().z > 4.0f)
            person.set_pos_z(4.0f);

        person.update();
    }

    // Player pos: forwards

    // Set camera relative to player
    camera.position.x = people.front().get_position().x - distance_to_camera;
    camera.target.x = camera.position.x + 10.0f;

    // Fire shots
    weapon_controller.update(people.front().get_position());
}

const std::vector<Person> &PlayerController::get_people() const
{
    return this->people;
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

const Person PlayerController::get_furthest_person() const
{
    auto furthest_person = people.front();

    for (const auto &person : people)
    {
        if (person.get_position().x > furthest_person.get_position().x)
        {
            furthest_person = person;
        }
    }

    return furthest_person;
}
