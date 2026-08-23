#include "triangle.hpp"

#include <iostream>
#include <cmath>

EquilateralTriangle::EquilateralTriangle(struct Point initialVertex, int height) {
    this->vertex1 = initialVertex;
    this->height = height;

    float c = this->height / std::sqrt(3); // Calculate the horizontal distance for the base vertices

    this->vertex2 = {this->vertex1.x - c , this->vertex1.y + this->height};
    this->vertex3 = {this->vertex1.x + c , this->vertex1.y + this->height};
}

EquilateralTriangle::~EquilateralTriangle() {
    // Destructor implementation (if needed)
}

void EquilateralTriangle::render(SDL_Renderer* renderer) {
    std::cout << "Rendering triangle with vertices: (" << vertex1.x << ", " << vertex1.y << "), ("
              << vertex2.x << ", " << vertex2.y << "), ("
              << vertex3.x << ", " << vertex3.y << ") and height: " << this->height << std::endl;

        SDL_Vertex* vertices = new SDL_Vertex[3];
        vertices[0] = {vertex1.x, vertex1.y};
        vertices[1] = {vertex2.x, vertex2.y};
        vertices[2] = {vertex3.x, vertex3.y};

        SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);

}