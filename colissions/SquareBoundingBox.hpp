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
    CollisionType intersect(const SquareBoundingBox& a, const SquareBoundingBox& b);

private:
    class GameObject* owner;
    bool hasIntersect(const class SquareBoundingBox& a, const class SquareBoundingBox& b);

};
