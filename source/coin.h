#include "main.h"
#include "vaporizer.h"

#ifndef COIN_H
#define COIN_H

class Coin : public Vaporizer
{
public:
    Coin() {}
    Coin(float x, float y, color_t color);
    // void add_sector(std::vector<GLfloat> &trias);
//     void get_pos(int &x, int &y);
//     void set_game_over(bool win_status = false);
//     bool is_game_over();
//     bool is_won();

// private:
//     bool game_over;
//     bool won;
};

#endif // COIN_H
