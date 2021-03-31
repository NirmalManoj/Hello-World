#include "main.h"
#include "ball.h"
#ifndef DECAGONAL_PRISM_H
#define DECAGONAL_PRISM_H

class DecagonalPrism : public Ball
{
public:
    DecagonalPrism() {}
    DecagonalPrism(float x, float y, color_t color);
};

#endif // DECAGONAL_PRISM_H
