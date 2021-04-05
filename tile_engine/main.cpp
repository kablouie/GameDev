#include <SFML/Graphics.hpp>

#include "game.h"
#include "player.h"
#include "levelSystem.h"

using namespace sf;
using namespace std;

unique_ptr<Player> player;

void Load() {
    player = make_unique<Player>();

    ls::loadLevelFile("res/levels/maze_2.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            if (ls::getTile({x,y}) == ls::START){
                Vector2f trueStart = { 50.0f , 50.0f };
                player->setPosition(ls::getTilePosition({ x , y }));
                player->move(trueStart);
            }
            
        }
    }

    // for (size_t y = 0; y < ls::getHeight(); ++y) {
    //     for (size_t x = 0; x < ls::getWidth(); ++x) {
           
    //     }
      
    // }


   
}

void Update(sf::RenderWindow& window) {

    // Reset clock, recalculate deltatime
    static Clock clock;
    double dt = clock.restart().asSeconds();

    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    player->Update(dt);

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
}

void Render(sf::RenderWindow& window) {

    ls::Render(window);
    player->Render(window);
    
}

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tile Engine");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}