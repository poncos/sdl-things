#pragma once

#include "MathDefinitions.hpp"

class SquareBoundingBox{

public:
    enum CollisionType {
        COLLISION_TOP,
        COLLISION_BOTTOM,
        COLLISION_LEFT,
        COLLISION_RIGHT,
        NONE,
    };

    SquareBoundingBox(class GameObject* owner): owner(owner) { }
    CollisionType intersect(const SquareBoundingBox& b);

    Vector2DF getPosition() const;
    Vector2DF getDimensions() const;

private:
    class GameObject* owner;
    bool hasIntersect(const class SquareBoundingBox& b);

};
