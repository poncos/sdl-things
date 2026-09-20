#include "MathDefinitions.hpp"


Vector2DI oneDimToTwoDim(int index, int rowLength, int itemWidth, int itemHeight) {
    Vector2DI result;
    int tileRow = index % rowLength;
    int tileCol = index / rowLength;

    result.x = tileRow * itemWidth;
    result.y = tileCol * itemHeight;

    return result;
}