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
    void set_game_over(bool win_status = false);
    bool is_game_over();
    bool is_won();

private:
    bool game_over;
    bool won;
};

#endif // PLAYER_H
