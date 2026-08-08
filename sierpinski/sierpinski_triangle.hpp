#pragma once

#include <vector>

#include "triangle.hpp"

class SierpinskiTriangle {
public:
    SierpinskiTriangle(const EquilateralTriangle initialTriangle);
    ~SierpinskiTriangle(); 
    
    void iterate();
    std::vector<EquilateralTriangle> getBlackTriangles() const { return this->blackTriangles; }
    std::vector<EquilateralTriangle> getWhiteTriangles() const { return this->whiteTriangles; }   
private:
    std::vector<EquilateralTriangle> splitTriangle(const EquilateralTriangle triangle);

    std::vector<EquilateralTriangle> blackTriangles;
    std::vector<EquilateralTriangle> whiteTriangles;
};