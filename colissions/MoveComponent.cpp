#include "MoveComponent.hpp"
#include "GameObject.hpp"

#include <iostream>

void MoveComponent::update(float deltaTime) {
    std::cout << "MoveComponent::update with deltaTime: " << deltaTime  << " ge: " << this->gravityEnabled <<
        " Speed: (" << this->speed.x << ", " << this->speed.y << ")" << 
    std::endl;

    if (this->gravityEnabled) {
        this->speed.y += GRAVITY * deltaTime;
    }

    Vector2DF position = this->owner->getPosition();
    Vector2DF objectDimensions = this->owner->getDimensions();
    position.x += this->speed.x * deltaTime;
    position.y += this->speed.y * deltaTime;
    

    enum Direction boundsCheck = this->checkBounds(position, objectDimensions);
    switch (boundsCheck) {
        case Direction::UP:
            std::cout << "MoveComponent::update UP bounds check" << std::endl;
            if (this->speed.y < 0) {
                position.y = 0;
                this->speed.y = 0;
            }
            break;
        case Direction::DOWN:
            std::cout << "MoveComponent::update DOWN bounds check" << std::endl;
            if (this->speed.y > 0) {
                position.y =
                    this->screenBounds.y - objectDimensions.y;
                this->speed.y = 0;
            }
            break;
        case Direction::LEFT:
            std::cout << "MoveComponent::update LEFT bounds check" << std::endl;
            if (this->speed.x < 0) {
                position.x = 0;
                this->speed.x = 0;
            }
            break;
        case Direction::RIGHT:
            std::cout << "MoveComponent::update RIGHT bounds check" << std::endl;
            if (this->speed.x > 0) {
                position.x =
                    this->screenBounds.x - objectDimensions.x;
                this->speed.x = 0;
            }
            break;
        default:
            break;
    }
    this->owner->setPosition(position);
}

enum Direction MoveComponent::checkBounds(Vector2DF position, Vector2DF objectDimensions) {

    if (this->screenBounds.x <= 0 || this->screenBounds.y <= 0)
        return Direction::NONE;

    if (position.x < 0) {
        return Direction::LEFT;
    } else if (position.x > this->screenBounds.x - objectDimensions.x) {
        return Direction::RIGHT;
    } else if (position.y < 0) {
        return Direction::UP;
    } else if (position.y > this->screenBounds.y - objectDimensions.y) {
        return Direction::DOWN;
    }

    return Direction::NONE;
}
