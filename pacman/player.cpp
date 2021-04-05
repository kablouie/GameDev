#include "player.h"
#include "game.h"
#include "levelSystem.h"
#include "system_renderer.h"
using namespace sf;
using namespace std;


void Player::Update(double dt) {

    //Move in four directions based on keys pressed

	Vector2f direction = { 0.0f, 0.0f };
	Vector2f playerOffsetX{ 10.0f, 0.0f };
	Vector2f playerOffsetY{ 0.0f, 10.0f };

	//Move up
	if (Keyboard::isKeyPressed(controls[0])) {
		if (ls::validMove(getPosition() - playerOffsetY)) {
			direction.y = -_speed * dt;
		}
	}

	//Move down
	if (Keyboard::isKeyPressed(controls[1])) {

		if (ls::validMove(getPosition() + playerOffsetY)) {
			direction.y = _speed * dt;
		}
	}

	//Move left
	if (Keyboard::isKeyPressed(controls[2])) {

		if (ls::validMove(getPosition() - playerOffsetX)) {
			direction.x = -_speed * dt;
		}
	}

	//Move right
	if (Keyboard::isKeyPressed(controls[3])) {

		if (ls::validMove(getPosition() + playerOffsetX)) {
			direction.x = _speed * dt;
		}

	}

	move(direction);
   
    Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(10.0f)) {
    _shape->setFillColor(Color::Yellow);
    _shape->setOrigin(Vector2f(10.0f, 10.0f));
}

void Player::Render(sf::RenderWindow& window) const {

	Renderer::queue(_shape.get());
    //window.draw(*_shape);
}