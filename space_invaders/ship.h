//ship.h
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Ship : public Sprite {
protected:
    IntRect _sprite;
    //Default constructor is hidden
    Ship();
    bool _exploded = false;
    float explodeTime = 0.3f;
public:
    bool is_exploded() const;
    //Constructor that takes a sprite
    explicit Ship(IntRect ir);
    //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
    virtual ~Ship() = 0;
    //Update, virtual so can be overridden, but not pure virtual
    virtual void Update(const float& dt);
    virtual void Explode();
};

class Invader : public Ship {
public:
    static bool invaderDirection;
    static float invaderSpeed;
    Invader(IntRect ir, Vector2f pos);
    Invader();
    void Update(const float& dt) override;
    void Explode() override;
};

class Player : public Ship {
public:
    float playerDirection = 0.0f;
    float playerSpeed = 80.0f;
    void Update(const float& dt) override;
    void Explode() override;
    Player();
};