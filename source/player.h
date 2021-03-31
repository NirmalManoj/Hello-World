#include "main.h"
#include "ball.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Ball
{
public:
    Player() {}
    Player(float x, float y, color_t color);
};

#endif // PLAYER_H
