#include<iostream>

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
    // thisSurface = SDLRect{one.getPosition().x, one.getPosition().y, one.getDimensions().x, one.getDimensions().y};
    // othersurface = SDLRect{other.getPosition().x, other.getPosition().y, other.getDimensions().x, other.getDimensions().y};

    // bool hasIntersection = SDL_HasIntersection(&thisSurface, &othersurface);
    // //std::cout << "HasIntersection between " << one.getName() << " and " << other.getName() << " is " << hasIntersection << std::endl;

    // return hasIntersection;
    return false; // Placeholder implementation
}

SquareBoundingBox::CollisionType SquareBoundingBox::intersect(const SquareBoundingBox& other) {
    // auto thisSurface = this->getSurface();
    // auto othersurface = other.getSurface();

    // std::cout << "Checking intersection between " << one.getName() << " and " << other.getName() 
    // << " Surfaces: [" << thisSurface.x << "," << thisSurface.y << "," << thisSurface.w << "," << thisSurface.h << "] and ["
    // << othersurface.x << "," << othersurface.y << "," << othersurface.w << "," << othersurface.h << "]"
    // << std::endl;

    // bool hasIntersection = SDL_HasIntersection(&thisSurface, &othersurface);
    // //std::cout << "HasIntersection between " << one.getName() << " and " << other.getName() << " is " << hasIntersection << std::endl;

    // if (!hasIntersection) {
    //     //std::cout << "NO intersecction" << std::endl;
    //     return NO_COLLISION;
    // }

    // // this->inCollision = hasIntersection;

    // auto thisPosition = one.getPosition();
    // auto otherPosition = other.getPosition();
    // auto thisDimensions = one.getDimensions();
    // auto otherDimensions = other.getDimensions();

    // // std::cout << "colission: thisY: " << thisPosition.y << " , otherY: " << otherPosition.y <<
    // //     " , thisX: " << thisPosition.x << ", otherX: " << otherPosition.x << " : " << std::endl;

    // float thisBottom = thisPosition.y + thisDimensions.y;
    // float thisRight = thisPosition.x + thisDimensions.x;
    // float otherBottom = otherDimensions.y + otherPosition.y;
    // float otherRight = otherDimensions.x + otherPosition.x;

    // float bottomOverlap = thisBottom - otherPosition.y;
    // float topOverlap = otherBottom - thisPosition.y;
    // float rightOverlap = thisRight - otherPosition.x;
    // float leftOverlap = otherRight - thisPosition.x;

    // if (isLowest(bottomOverlap, {topOverlap, rightOverlap, leftOverlap})) {
    //     //std::cout << "BOTTOM COLLISION" << std::endl;
    //     return SQUARE_COLLISION_BOTTOM;
    // } else if (isLowest(topOverlap, {bottomOverlap, rightOverlap, leftOverlap})) {
    //     //std::cout << "TOP COLLISION" << std::endl;
    //     return SQUARE_COLLISION_TOP;
    // } else if (isLowest(rightOverlap, {bottomOverlap, topOverlap, leftOverlap})) {
    //     //std::cout << "RIGHT COLLISION" << std::endl;
    //     return SQUARE_COLLISION_RIGHT;
    // } else {
    //     //std::cout << "LEsFT COLLISION" << std::endl;
    //     return SQUARE_COLLISION_LEFT;
    // }
    return CollisionType::NONE; // Placeholder implementation
}