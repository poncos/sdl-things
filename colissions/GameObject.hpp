#pragma once

#include "MathDefinitions.hpp"
#include "SquareBoundingBox.hpp"
#include "MoveComponent.hpp"

#include "SDL3/SDL.h"

class GameObject {
public:
    GameObject(struct Vector2DF position, struct Vector2DF dimensions);
    virtual ~GameObject();

    virtual void update(float deltaTime);
    virtual void render(SDL_Renderer* renderer);

    struct Vector2DF getPosition() const { return position; }
    void setPosition(const struct Vector2DF& newPosition) { position = newPosition; }
    struct Vector2DF getDimensions() const { return dimensions; }
    void setDimensions(const struct Vector2DF& newDimensions) { dimensions = newDimensions; }
    void setColor(const struct Vector3DI& newColor) { color = newColor; }

private:
    struct Vector2DF position;
    struct Vector2DF dimensions;
    struct Vector3DI color{255, 0, 0}; // Default color is red

    SquareBoundingBox* boundingBox;
    MoveComponent* moveComponent;
};