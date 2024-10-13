#pragma once
#include "raylib.h"
#include <vector>
#include "WeaponController.hpp"
#include "Gate.hpp"
#include "Person.hpp"

class PlayerController
{
public:
    PlayerController();
    const Camera &get_camera() const;
    void render();
    void update();
    const std::vector<Person> &get_people() const;
    const int get_stats() const;
    void set_stats(int new_value);
    void update_stats(GateType gate_type, int gate_value);
    const WeaponController &get_weapon_controller() const;
    WeaponController &get_weapon_controller();
    const Person get_furthest_person() const;

private:
    Camera camera;
    float speed;
    float distance_to_camera;

    int stats;

    std::vector<Person> people;

    WeaponController weapon_controller;
};