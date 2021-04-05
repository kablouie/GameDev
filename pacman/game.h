#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;



constexpr uint16_t totalGhosts = 4;
constexpr uint16_t gameWidth = 700;
constexpr uint16_t gameHeight = 725;


//extern EntityManager em;

const Keyboard::Key controls[4] = {
    Keyboard::W,    // UP
    Keyboard::S,    // Down
    Keyboard::A,   // Left
    Keyboard::D,  // Right
};

const Color colors[4] = {
    Color::Red,
    Color::Magenta,
    Color::Cyan,
    Color::Blue,
};

