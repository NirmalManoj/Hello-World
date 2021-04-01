#include "main.h"
#include "vaporizer.h"

#ifndef TASK_H
#define TASK_H

class Task : public Vaporizer
{
public:
    Task() {}
    Task(float x, float y, color_t color);
// void add_sector(std::vector<GLfloat> &trias);
//     void get_pos(int &x, int &y);
//     void set_game_over(bool win_status = false);
//     bool is_game_over();
//     bool is_won();

// private:
//     bool game_over;
//     bool won;
};

#endif // TASK_H
