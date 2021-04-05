#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Bullet : public sf::Sprite {
public:
	//updates All bullets
	static void Update(const float& dt);
	//Render's All bullets
	static void Render(RenderWindow& window);
	//Chose an inactive bullet and use it.
	static void Fire(const Vector2f& pos, const bool mode);

	~Bullet() = default;
protected:
	static unsigned char bulletPointer;
	static Bullet bullets[256];
	//Called by the static Update()
	void _Update(const float& dt);
	//Never called by our code
	Bullet();
	//false=player bullet, true=Enemy bullet
	bool _mode;
};