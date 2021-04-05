#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

//const Keyboard::Key controls[5] = {
//    Keyboard::W,    // UP
//    Keyboard::S,    // Down
//    Keyboard::A,   // Left
//    Keyboard::D,  // Right
//    Keyboard::Space, // Shoot
//};

Texture(spritesheet);
vector<Ship*> ships;
Player* player = new Player();

float cordX = 100.f;
float cordY = 100.f;
int spriteSheetX = 0;
int spriteSheetY = 0;
const int spriteX = 32;
const int spriteY = 32;
const int increment = 32;



//Own method that creates the rows of invaders
//void Invaders() {
//
//    for (int i = 0; i < 5; i++) {
//
//        cordX = 100.f;
//
//        for (int i = 0; i < 12; i++) {
//
//            Invader* invader = new Invader(sf::IntRect(spriteSheetX, spriteSheetY, spriteX, spriteY), { cordX,cordY });
//            ships.push_back(invader);
//            cordX += increment;
//        }
//        cordY += increment;
//        spriteSheetX += increment;
//    }
//
//    cordX = 100.f;
//    cordY = 100.f;
//    spriteSheetX = 0;
//    spriteSheetY = 0;
//}



void Load() {
    if (!spritesheet.loadFromFile("res/sprites/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << endl;
    }

    for (int r = 0; r < invaders_rows; ++r) {

        cordX = 100.f;
        auto rect = IntRect(spriteSheetX,spriteSheetY,spriteX,spriteY);

        for (int c = 0; c < invaders_columns; ++c) {
            Vector2f position = { cordX,cordY };
            auto invader = new Invader(rect, position);
            ships.push_back(invader);
            cordX += increment;
        }

        cordY += increment;
        spriteSheetX += increment;   
    }

    cordX = 100.f;
    cordY = 100.f;
    spriteSheetX = 0;

    ships.push_back(player);

    Invader::invaderSpeed = 20.0f;
}

void Reset() {

    cordX = 100.f;
    auto rect = IntRect(spriteSheetX, spriteSheetY, spriteX, spriteY);

    for (int c = 0; c < invaders_columns; ++c) {
        Vector2f position = { cordX,cordY };
        auto invader = new Invader(rect, position);
        ships.push_back(invader);
        cordX += increment;
    }

    cordY += increment;
    spriteSheetX += increment;


    cordX = 100.f;
    cordY = 100.f;
    spriteSheetX = 0;

    ships.push_back(player);

    Invader::invaderSpeed = 20.0f; 
}

void Update(RenderWindow & window) {

        // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    for (auto& s : ships) {
        s->Update(dt);
    }

    Bullet::Update(dt);

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
}


void Render(RenderWindow& window) {
    //window.draw(invader);

    for (const auto s : ships) {
        window.draw(*s);
    }  

    Bullet::Render(window);
  
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE_INVADERS");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}

//int main(){
// sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
// sf::CircleShape shape(100.f);
// shape.setFillColor(sf::Color::Green);
//
// while (window.isOpen()){
//     sf::Event event;
//     while (window.pollEvent(event)){
//     if (event.type == sf::Event::Closed){
//       window.close();
//     }
//   }
//   window.clear();
//   window.draw(shape);
//   window.display();
// }
// return 0;
//}