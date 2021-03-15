#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int spin_axis;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void start_spin();
    void stop_spin();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
