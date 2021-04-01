#include "main.h"
#include "player.h"

#ifndef VAPORIZER_H
#define VAPORIZER_H

class Vaporizer : public Player
{
public:
    Vaporizer() {}
    Vaporizer(float x, float y, color_t color);
    void add_sector(std::vector<GLfloat> &trias);
//     void get_pos(int &x, int &y);
//     void set_game_over(bool win_status = false);
//     bool is_game_over();
//     bool is_won();

// private:
//     bool game_over;
//     bool won;
};

#endif // VAPORIZER_H
