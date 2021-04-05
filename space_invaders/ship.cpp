//ship.cpp
#include "game.h"
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Ship::Ship() {};
Invader::Invader() : Ship() {};

bool Invader::invaderDirection;
float Invader::invaderSpeed;


Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
}

void Ship::Update(const float& dt) {

}

void Ship::Explode() {

	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}

bool Ship::is_exploded() const { 
	if (_exploded == true) {
		return true;
	}
	else {
		return false;
	}
}


Invader::Invader(IntRect ir, Vector2f pos) : Ship(ir) {
	setOrigin(16,16);
	setPosition(pos);
}

void Invader::Update(const float& dt) {

	static float firetime = 0.0f;
	firetime -= dt;

	if (_exploded && explodeTime >= 0){
		explodeTime -= dt;
		if (explodeTime <= 0) {
			Explode();
		}
	}

	if (firetime <= 0 && rand() % 100 == 0) {
		if (!_exploded) {
			Bullet::Fire(getPosition(), true);
			firetime = 4.0f + (rand() % 60);
		}
	}

	move(dt * (invaderDirection ? 1.0f : -1.0f) * invaderSpeed, 0);

	if ((invaderDirection && getPosition().x > gameWidth - 16) ||
		(!invaderDirection && getPosition().x < 16)) {

		invaderDirection = !invaderDirection;

		for (auto s : ships) {
			if (s != player) {
				s->move(0, 24);
			}
		}
	}
}

void Invader::Explode() {
	if (!_exploded) {
		Ship::Explode();
	}
	else {
		setTextureRect(IntRect(0, 0, 0, 0));
	}

}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {

	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {

	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}

	playerDirection = 0.0f;

	if (Keyboard::isKeyPressed(controls[2]) && getPosition().x > 0) {
		playerDirection--;
	}

	if (Keyboard::isKeyPressed(controls[3]) && getPosition().x + 32 < gameWidth) {
		playerDirection++;
	}
	move(playerDirection * playerSpeed * dt, 0);
}

void Player::Explode() {
	Ship::Explode();
	
}


//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;