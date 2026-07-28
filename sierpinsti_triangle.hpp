#pragma once

#include <vector>

#include "triangle.hpp"

class SierpinskiTriangle {
public:
    SierpinskiTriangle(const EquilateralTriangle initialTriangle, int height, int depth);
    ~SierpinskiTriangle(); 
    
    void iterate();
    std::vector<const EquilateralTriangle> getBlackTriangles() const { return this->blackTriangles; }
    std::vector<const EquilateralTriangle> getWhiteTriangles() const { return this->whiteTriangles; }   
private:
    std::vector<const EquilateralTriangle> splitTriangle(const EquilateralTriangle triangle);

    std::vector<const EquilateralTriangle> blackTriangles;
    std::vector<const EquilateralTriangle> whiteTriangles;
};