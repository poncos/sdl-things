#include "triangle.hpp"

#include <iostream>

EquilateralTriangle::EquilateralTriangle(struct Point initialVertex, int height) {
    this->initialVertex = initialVertex;
    this->height = height;
}

EquilateralTriangle::~EquilateralTriangle() {
    // Destructor implementation (if needed)
}

void EquilateralTriangle::render(SDL_Renderer* renderer) {
    // Calculate the vertices of the equilateral triangle
    float c = this->height / sqrt(3); // Calculate the horizontal distance for the base vertices

    struct Point vertex1 = this->initialVertex;
    struct Point vertex2 = {this->initialVertex.x - c , this->initialVertex.y + this->height};
    struct Point vertex3 = {this->initialVertex.x + c , this->initialVertex.y + this->height};
    
    std::cout << "Rendering triangle with vertices: (" << vertex1.x << ", " << vertex1.y << "), ("
              << vertex2.x << ", " << vertex2.y << "), ("
              << vertex3.x << ", " << vertex3.y << ")" << std::endl;

    SDL_Vertex vertices[3];
    vertices[0] = {vertex1.x, vertex1.y};
    vertices[1] = {vertex2.x, vertex2.y};
    vertices[2] = {vertex3.x, vertex3.y};

    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
    // Draw the triangle using SDL_RenderDrawLine
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Set color to red
    // SDL_RenderDrawLine(renderer, vertex1.x, vertex1.y, vertex2.x, vertex2.y);
    // SDL_RenderDrawLine(renderer, vertex2.x, vertex2.y, vertex3.x, vertex3.y);
    // SDL_RenderDrawLine(renderer, vertex3.x, vertex3.y, vertex1.x, vertex1.y);


}