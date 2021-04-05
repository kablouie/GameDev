#include <SFML/Graphics.hpp>
#include "ghost.h"
#include "game.h"
#include "player.h"
#include "levelSystem.h"
#include "system_renderer.h"
#include "pacman.h"


using namespace sf;
using namespace std;

//EntityManager em;

//auto player = make_shared<Player>();
//
//void generateEntities() {
//
//    for (int g = 0; g < totalGhosts; g++) {
//        em.list.push_back(make_shared<Ghost>());
//    }
//
//    em.list.push_back(player);
//
//}
//
//void setEntityPositions() {
//
//    int startPosCounter = 0;
//    vector<Vector2f> ghoststarts;
//    Vector2f center{ 12.5f , 12.5f };
//
//    for (size_t y = 0; y < ls::getHeight(); ++y) {
//        for (size_t x = 0; x < ls::getWidth(); ++x) {
//
//            if (ls::getTile({ x,y }) == ls::ENEMY) {
//                ghoststarts.push_back(ls::getTilePosition({ x,y }));
//            }
//            
//            if (ls::getTile({ x,y }) == ls::START) {
//                for (auto e : em.list) {
//                    if (e == player) {
//                        e->setPosition(ls::getTilePosition({ x,y }));
//                        e->move(center);
//                    }
//                }
//            }
//        }
//    }
//
//    for (auto e : em.list) {
//        
//        if (e != player) {
//            e->setPosition(ghoststarts[startPosCounter]);
//            e->move(center);
//        }
//        startPosCounter++;
//    }
//
//}

void Load() {

    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->load();
    menuScene->load();

    // Start at main menu
    activeScene = menuScene;

 

    //generateEntities();

    //setEntityPositions();

    //// Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }
}

void Update(sf::RenderWindow& window) {

    // Reset clock, recalculate deltatime
    static Clock clock;
    double dt = clock.restart().asSeconds();
    activeScene->update(dt); 

    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    //em.update(dt);

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
}

void Render(sf::RenderWindow& window) {

    //ls::Render(window);
    Renderer::initialise(window);

    activeScene->render();
    
    Renderer::render();
}

int main(){
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pacman");
    //Renderer::initialise(window);
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}