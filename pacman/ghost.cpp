#include "ghost.h"
#include "game.h"
#include "levelSystem.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

vector<string> validMoves;
Vector2f direction = { 0.0f, 0.0f };

void Ghost::CheckValidMoves() {

    Vector2f ghostOffsetX{ 12.5f, 0.0f };
    Vector2f ghostOffsetY{ 0.0f, 12.5f };

    if (ls::validMove(getPosition() - ghostOffsetY)) {
        string up = "up";
        validMoves.push_back(up);
    }

    if (ls::validMove(getPosition() + ghostOffsetY)) {
        string down = "down";
        validMoves.push_back(down);
    }

    if (ls::validMove(getPosition() - ghostOffsetX)) {
        string left = "left";
        validMoves.push_back(left);
    }
  
    if (ls::validMove(getPosition() + ghostOffsetX)) {
        string right = "right";
        validMoves.push_back(right);
    }
}



  

void Ghost::Update(double dt) {
	move(direction);

    Entity::Update(dt); 

    validMoves.clear();
}

Ghost::Ghost()
    : _speed(200.0f), Entity(make_unique<CircleShape>(10.0f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(10.0f, 10.0f));
}

void Ghost::Render(sf::RenderWindow& window) const {
    Renderer::queue(_shape.get());
}