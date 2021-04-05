#pragma once
#include "entity.h"
#include <vector>

class Ghost : public Entity {
private:

    float _speed;

public:
	void Update(double dt) override;
	void CheckValidMoves();
	void Seek(double dt);
	Ghost();
	void Render(sf::RenderWindow& window) const override;
};