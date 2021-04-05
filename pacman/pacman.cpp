#include <SFML/Graphics.hpp>
#include "game.h"
#include "player.h"
#include "ghost.h"
#include "scene.h"
#include "pacman.h"
#include "levelSystem.h"
#include "system_renderer.h"

void Scene::render() {

    _ents.render(Renderer::getWindow());
}
void Scene::update(double dt) {

    _ents.update(dt);
}

std::vector<std::shared_ptr<Entity>> &Scene::getEnts() { return _ents.list; }

std::shared_ptr<Scene> gameScene; 
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

void MenuScene::update(double dt) {
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        activeScene = gameScene;
    }
   
	text.setString("Almost Pacman");

    
}

void MenuScene::render() {
	Renderer::queue(&text);
    Scene::render();
}

void MenuScene::load() {
	
	font.loadFromFile("res/fonts/Goldaman-Regular");
	text.setFont(font);
	text.setCharacterSize(25 );
	text.setPosition(gameWidth * 0.5 - text.getLocalBounds().getSize().x, gameHeight * 0.5 - (text.getLocalBounds().getSize().y * 0.5));

}

void MenuScene::reset(std::shared_ptr<Scene> menuS) {
    menuScene = menuS;
}




void GameScene::respawn()
{

}

void GameScene::update(double dt) {
    if (Keyboard::isKeyPressed(Keyboard::Tab)) {
        activeScene = menuScene;
    }
    for (auto ent : getEnts()) {
        ent->Update(dt);
    }
}

void GameScene::render() {

    ls::Render(Renderer::getWindow());
    for (auto ent : getEnts()) {
        ent->Render(Renderer::getWindow());
    }
}

void GameScene::load() {

	float tileSize = 25.0f;
	ls::loadLevelFile("res/levels/pacman_maze.txt", tileSize);
	
	auto player = make_shared<Player>();
	_ents.list.push_back(player);

	for (int g = 0; g < totalGhosts; g++) {
		_ents.list.push_back(make_shared<Ghost>());
	}

    int startPosCounter = 0;
    vector<Vector2f> ghoststarts;
    Vector2f center{ 12.5f , 12.5f };

    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {

            if (ls::getTile({ x,y }) == ls::ENEMY) {
                ghoststarts.push_back(ls::getTilePosition({ x,y }));
            }

            if (ls::getTile({ x,y }) == ls::START) {
                for (auto e : _ents.list) {
                    if (e == player) {
                        e->setPosition(ls::getTilePosition({ x,y }));
                        e->move(center);
                    }
                }
            }
        }
    }

    /*for (int i = 1; i < 5; i++) {
        _ents.list[i]->setPosition(ghoststarts[startPosCounter]);
        _ents.list[i]->move(center);
        startPosCounter++;
    }*/

    for (auto e : _ents.list) {

        if (e != player) {
            e->setPosition(ghoststarts[startPosCounter]);
            e->move(center);
            startPosCounter++;
        }
        //startPosCounter++;
    }

}

void GameScene::reset(std::shared_ptr<Scene> gameS) {
    gameScene = gameS;
}
	
