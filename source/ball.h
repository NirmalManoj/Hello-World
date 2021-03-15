#include "main.h"

#ifndef BALL_H
#define BALL_H

class Ball
{
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 initial_position;
    float rotation;
    int spin_axis;
    void draw(glm::mat4 VP);
    void move_position(glm::vec3 x);
    void set_position(float x, float y);
    void reset_position();
    void tick();
    void start_spin();
    void stop_spin();
    float get_ang(float x);
    double speed;

protected:
    VAO *object;
};

#endif // BALL_H
