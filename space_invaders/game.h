//game.h
#pragma once
#include <SFML/Graphics.hpp>
#include "ship.h"
#include "bullet.h"

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 12;


extern Texture spritesheet;
extern vector<Ship*> ships;
extern Player* player;

const Keyboard::Key controls[5] = {
    Keyboard::W,    // UP
    Keyboard::S,    // Down
    Keyboard::A,   // Left
    Keyboard::D,  // Right
    Keyboard::Space, // Shoot
};