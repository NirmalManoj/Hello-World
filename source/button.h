#include "main.h"
#include "vaporizer.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button : public Vaporizer
{
public:
    Button() {}
    Button(float x, float y, color_t color);
    // void add_sector(std::vector<GLfloat> &trias);
//     void get_pos(int &x, int &y);
//     void set_game_over(bool win_status = false);
//     bool is_game_over();
//     bool is_won();

// private:
//     bool game_over;
//     bool won;
};

#endif // BUTTON_H
