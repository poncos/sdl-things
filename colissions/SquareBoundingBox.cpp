#include<iostream>
#include<SDL3/SDL.h>

#include "SquareBoundingBox.hpp"
#include "GameObject.hpp"

#include <vector>

Vector2DF SquareBoundingBox::getPosition() const {
    return this->owner->getPosition();
}

Vector2DF SquareBoundingBox::getDimensions() const {
    return this->owner->getDimensions();
}

bool isLowest(float value, std::vector<float> otherValues) {
    
    for (float &otherValue : otherValues) {
        if (value >= otherValue)
            return false;
        otherValue++;
    }

    return true;
}

bool SquareBoundingBox::hasIntersect(const SquareBoundingBox& other) {
    SDL_Rect thisSurface = SDL_Rect{ 
        (int)this->owner->getPosition().x,
        (int)this->owner->getPosition().y,
        (int)this->owner->getDimensions().x,
        (int)this->owner->getDimensions().y
    };

    SDL_Rect othersurface = SDL_Rect{ 
        (int)other.owner->getPosition().x, 
        (int)other.owner->getPosition().y, 
        (int)other.owner->getDimensions().x,
        (int)other.owner->getDimensions().y
    };

    bool hasIntersection = SDL_HasRectIntersection(&thisSurface, &othersurface);
    // std::cout << "HasIntersection between " << hasIntersection << std::endl;

    return hasIntersection;
}

SquareBoundingBox::CollisionType SquareBoundingBox::intersect(const SquareBoundingBox& other) {
    // auto thisSurface = this->getSurface();
    // auto othersurface = other.getSurface();
    bool hasIntersection = this->hasIntersect(other);

    if (!hasIntersection) {
        return CollisionType::NONE;
    }

    auto thisPosition = this->getPosition();
    auto otherPosition = other.getPosition();
    auto thisDimensions = this->getDimensions();
    auto otherDimensions = other.getDimensions();

    float thisBottom = thisPosition.y + thisDimensions.y;
    float thisRight = thisPosition.x + thisDimensions.x;
    float otherBottom = otherDimensions.y + otherPosition.y;
    float otherRight = otherDimensions.x + otherPosition.x;

    float bottomOverlap = thisBottom - otherPosition.y;
    float topOverlap = otherBottom - thisPosition.y;
    float rightOverlap = thisRight - otherPosition.x;
    float leftOverlap = otherRight - thisPosition.x;

    if (isLowest(bottomOverlap, {topOverlap, rightOverlap, leftOverlap})) {
        //std::cout << "BOTTOM COLLISION" << std::endl;
        return CollisionType::BOTTOM;
    } else if (isLowest(topOverlap, {bottomOverlap, rightOverlap, leftOverlap})) {
        //std::cout << "TOP COLLISION" << std::endl;
        return CollisionType::TOP;
    } else if (isLowest(rightOverlap, {bottomOverlap, topOverlap, leftOverlap})) {
        //std::cout << "RIGHT COLLISION" << std::endl;
        return CollisionType::RIGHT;
    } else {
        //std::cout << "LEsFT COLLISION" << std::endl;
        return CollisionType::LEFT;
    }
    return CollisionType::NONE; // Placeholder implementation
}