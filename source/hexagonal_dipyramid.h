#include "main.h"
#include "ball.h"
#ifndef HEXAGONAL_DIPYRAMID_H
#define HEXAGONAL_DIPYRAMID_H

class HexagonalDipyramid : public Ball
{
public:
    HexagonalDipyramid() {}
    HexagonalDipyramid(float x, float y, color_t color);
};

#endif // HEXAGONAL_DIPYRAMID_H
