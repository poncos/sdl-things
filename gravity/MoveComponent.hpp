#pragma once

#define GRAVITY 900.0f // pixels per second squared

struct Vector2DF {
    float x;
    float y;
};

struct Vector2DI {
    int x;
    int y;
};

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class MoveComponent {
public:
    MoveComponent(
        struct Vector2DF position = {0, 0},
        struct Vector2DF speed = {0, 0},
        struct Vector2DF direction = {0, 0},
        struct Vector2DF objectDimensions = {0, 0},
        bool gravityEnabled = false,
        struct Vector2DI screenBounds = {0, 0}) :
            position(position),
            velocity(speed),
            direction(direction),
            gravityEnabled(gravityEnabled),
            objectDimensions(objectDimensions),
            screenBounds(screenBounds) { }

    
    void setSpeed(struct Vector2DF speed) { this->velocity = speed; }
    struct Vector2DF getPosition() { return this->position; }
    void setDirection(struct Vector2DF direction) { this->direction = direction; }
    void update(float deltaTime);

private:
    bool gravityEnabled = false;
    struct Vector2DI screenBounds;
    struct Vector2DF velocity = {0, 0};
    struct Vector2DF direction = {0, 0};
    struct Vector2DF position = {0, 0};
    struct Vector2DF objectDimensions = {0, 0};

    enum Direction checkBounds();

};