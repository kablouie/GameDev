#pragma once
#include "entity.h"

class Player : public Entity {
private:
	float _speed = 80.0f;
	

public:

	void Update(double dt) override;
	Player();
	void Render(sf::RenderWindow& window) const override;
};