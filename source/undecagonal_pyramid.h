#include "main.h"
#include "ball.h"
#ifndef UNDECAGONAL_PYRAMID_H
#define UNDECAGONAL_PYRAMID_H

class UndecagonalPyramid : public Ball
{
public:
    UndecagonalPyramid() {}
    UndecagonalPyramid(float x, float y, color_t color);
};

#endif // UNDECAGONAL_PYRAMID_H
