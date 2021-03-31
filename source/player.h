#include "main.h"
#include "ball.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Ball
{
public:
    Player() {}
    Player(float x, float y, color_t color);
    void add_sector(std::vector<GLfloat> &trias);
    void get_pos(int &x, int &y);
};

#endif // PLAYER_H
