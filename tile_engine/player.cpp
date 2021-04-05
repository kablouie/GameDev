#include "player.h"
#include "game.h"
#include "levelSystem.h"

using namespace sf;
using namespace std;


void Player::Update(double dt) {
    //Move in four directions based on keys

	Vector2f direction = { 0.0f, 0.0f };
    
	
	if (Keyboard::isKeyPressed(controls[0])) {
		for (size_t y = 0; y < ls::getHeight(); ++y) {
        	for (size_t x = 0; x < ls::getWidth(); ++x) {
				if (ls::getTile({x,y}) == ls::WALL) {
					Vector2f tilePosition = ls::getTilePosition({x,y});
					if (//getPosition().x > tilePosition.x &&
						//getPosition().x < tilePosition.x + tileOffset &&
						getPosition().y - playerOffset > tilePosition.y + tileOffset) {

						direction.y = -_speed * dt;
					}
				}
        	}
    	}
	}

	if (Keyboard::isKeyPressed(controls[1])) {
		for (size_t y = 0; y < ls::getHeight(); ++y) {
        	for (size_t x = 0; x < ls::getWidth(); ++x) {
				if (ls::getTile({x,y}) == ls::WALL) {
					const FloatRect boundingBox = _shape.getGlobalBounds();
					//Vector2f tilePosition = ls::getTilePosition({x,y});
					if (//getPosition().x > tilePosition.x &&
						//getPosition().x < tilePosition.x + tileOffset &&
						//getPosition().y < tilePosition.y
						!tempTile.getGlobalBounds().intersects(boundingBox)) {

						direction.y = _speed * dt;
					}
				}
        	}
    	}
	}

	if (Keyboard::isKeyPressed(controls[2])) {
		for (size_t y = 0; y < ls::getHeight(); ++y) {
        	for (size_t x = 0; x < ls::getWidth(); ++x) {
				if (ls::getTile({x,y}) == ls::WALL) {
					Vector2f tilePosition = ls::getTilePosition({x,y});
					if (//getPosition().y > tilePosition.y &&
						//getPosition().y < tilePosition.y + tileOffset &&
						getPosition().x > tilePosition.x + tileOffset) {

						direction.x = -_speed * dt;
					}
				}
        	}
    	}	
	}

	if (Keyboard::isKeyPressed(controls[3])) {
		for (size_t y = 0; y < ls::getHeight(); ++y) {
        	for (size_t x = 0; x < ls::getWidth(); ++x) {
				if (ls::getTile({x,y}) == ls::WALL) {
					Vector2f tilePosition = ls::getTilePosition({x,y});
					if (//getPosition().y > tilePosition.y &&
						//getPosition().y < tilePosition.y + tileOffset &&
						getPosition().x < tilePosition.x) {

						direction.x = _speed * dt;
					}
				}
        	}
    	}	
	}

	move(direction);
   
    Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}