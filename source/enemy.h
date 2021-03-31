#include "main.h"
#include "player.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Player
{
public:
    Enemy() {}
    Enemy(float x, float y, color_t color);
};

#endif // ENEMY_H
