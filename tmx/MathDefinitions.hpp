#pragma once

struct Vector2DI {
    int x;
    int y;
};

Vector2DI oneDimToTwoDim(int index, int rowLength, int itemWidth, int itemHeight);