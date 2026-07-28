#include "sierpinski_triangle.hpp"

SierpinskiTriangle::SierpinskiTriangle(const EquilateralTriangle initialTriangle, int height, int depth) {
    this->blackTriangles.push_back(initialTriangle);
}

SierpinskiTriangle::~SierpinskiTriangle() {
    // Destructor implementation (if needed)
}

void SierpinskiTriangle::iterate() {
    
    for (const auto& triangle : this->blackTriangles) {
        auto newTriangles = this->splitTriangle(triangle);
        this->blackTriangles.insert(this->blackTriangles.end(), newTriangles.begin(), newTriangles.end());
    }
}

std::vector<const EquilateralTriangle> SierpinskiTriangle::splitTriangle(const EquilateralTriangle triangle) {
    std::vector<const EquilateralTriangle> newTriangles;
    float y_top = triangle.height + triangle.initialVertex.y;
    float x_bottom = triangle.initialVertex.x;

    // Calculate the vertices of the current triangle
    float c = triangle.height / sqrt(3); // Calculate the horizontal distance for the base vertices

    struct Point vertex1 = triangle.initialVertex;
    struct Point vertex2 = {triangle.initialVertex.x - c, triangle.initialVertex.y + triangle.height};
    struct Point vertex3 = {triangle.initialVertex.x + c, triangle.initialVertex.y + triangle.height};

    // Create three new triangles by connecting the midpoints of the sides
    struct Point midpoint1 = {(vertex1.x + vertex2.x) / 2, (vertex1.y + vertex2.y) / 2};
    struct Point midpoint2 = {(vertex2.x + vertex3.x) / 2, (vertex2.y + vertex3.y) / 2};
    struct Point midpoint3 = {(vertex3.x + vertex1.x) / 2, (vertex3.y + vertex1.y) / 2};

    int newHeight = triangle.height / 2;

    newTriangles.push_back(EquilateralTriangle(vertex1, newHeight));
    newTriangles.push_back(EquilateralTriangle(midpoint1, newHeight));
    newTriangles.push_back(EquilateralTriangle(midpoint3, newHeight));

    return newTriangles;
}