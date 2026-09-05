#pragma once

#include "MathDefinitions.hpp"
#include "SquareBoundingBox.hpp"

#include "SDL3/SDL.h"

class GameObject {
public:
    GameObject(struct Vector2DF position, struct Vector2DF dimensions);
    virtual ~GameObject() { }

    virtual void update(float deltaTime) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;

    struct Vector2DF getPosition() const { return position; }
    void setPosition(const struct Vector2DF& newPosition) { position = newPosition; }
    struct Vector2DF getDimensions() const { return dimensions; }
    void setDimensions(const struct Vector2DF& newDimensions) { dimensions = newDimensions; }

private:
    struct Vector2DF position;
    struct Vector2DF dimensions;

    SquareBoundingBox* boundingBox;
};