#pragma once

#include "MathDefinitions.hpp"

class MoveComponent {
public:

    enum ScreenBoundBehavior {
        STOP_AT_BOUNDS,
        WRAP_AROUND,
        NONE
    };

    MoveComponent(
        class GameObject* owner,
        struct Vector2DF speed = {0, 0},
        bool gravityEnabled = false,
        struct Vector2DI screenBounds = {0, 0},
        ScreenBoundBehavior screenBoundBehavior = NONE
    ) :
            owner(owner),
            speed(speed),
            gravityEnabled(gravityEnabled),
            screenBounds(screenBounds),
            screenBoundBehavior(screenBoundBehavior) { }
    void update(float deltaTime);
    
    void setSpeed(struct Vector2DF speed) { this->speed = speed; }
    enum Direction getScreenBoundStatus() const { return this->screenBoundStatus; }

private:
    class GameObject* owner;
    bool gravityEnabled = false;
    struct Vector2DI screenBounds;
    struct Vector2DF speed = {0, 0};
    enum Direction screenBoundStatus = Direction::NONE;
    enum ScreenBoundBehavior screenBoundBehavior = ScreenBoundBehavior::NONE;

    enum Direction checkBounds(struct Vector2DF position, struct Vector2DF objectDimensions);

};