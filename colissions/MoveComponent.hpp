#pragma once

#include "MathDefinitions.hpp"

class MoveComponent {
public:
    MoveComponent(
        class GameObject* owner,
        struct Vector2DF speed = {0, 0},
        bool gravityEnabled = false,
        struct Vector2DI screenBounds = {0, 0}) :
            owner(owner),
            speed(speed),
            gravityEnabled(gravityEnabled),
            screenBounds(screenBounds) { }
    void update(float deltaTime);
    
    void setSpeed(struct Vector2DF speed) { this->speed = speed; }

private:
    class GameObject* owner;
    bool gravityEnabled = false;
    struct Vector2DI screenBounds;
    struct Vector2DF speed = {0, 0};

    enum Direction checkBounds(struct Vector2DF position, struct Vector2DF objectDimensions);

};