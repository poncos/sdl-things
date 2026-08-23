#include "sierpinski_triangle.hpp"

#include <iostream>
#include <cmath>

SierpinskiTriangle::SierpinskiTriangle(const EquilateralTriangle initialTriangle) {
    this->blackTriangles.push_back(initialTriangle);
}

SierpinskiTriangle::~SierpinskiTriangle() {
    // Destructor implementation (if needed)
}

void SierpinskiTriangle::iterate() {
    std::vector<EquilateralTriangle> newBlackTriangles;

    for (const auto& triangle : this->blackTriangles) {
        std::cout << "Iterating..." << std::endl;
        auto splitTriangles = this->splitTriangle(triangle);
        newBlackTriangles.insert(newBlackTriangles.end(), splitTriangles.begin(), splitTriangles.end());
    }
    this->blackTriangles.clear();
    this->blackTriangles = newBlackTriangles;
}

std::vector<EquilateralTriangle> SierpinskiTriangle::splitTriangle(const EquilateralTriangle triangle) {
    std::vector<EquilateralTriangle> newTriangles;
    
    float newHeight = triangle.height / 2.0f; // Calculate the new height for the smaller triangles
    float c2 = newHeight / std::sqrt(3); // Calculate the horizontal distance for the

    struct Point vertex1 = triangle.vertex1;
    struct Point vertex2 = {vertex1.x - c2, vertex1.y + newHeight};
    struct Point vertex3 = {vertex1.x + c2, vertex1.y + newHeight};

    newTriangles.push_back(EquilateralTriangle(vertex1, newHeight));
    newTriangles.push_back(EquilateralTriangle(vertex2, newHeight));
    newTriangles.push_back(EquilateralTriangle(vertex3, newHeight));

    return newTriangles;
}