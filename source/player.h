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

    void add_health(int x);
    void dec_health(int x);
    void add_task();
    void dec_time();
    int get_health();
    int get_task_done();
    int get_time();

private:
    bool game_over;
    bool won;
    int health;
    int task_done;
    int time_left;
};

#endif // PLAYER_H
