#ifndef MAZE_H
#define MAZE_H

#include "main.h"
#include <vector>
// using namespace std;
class Maze
{
public:
    Maze() {}
    Maze(float x, float y, color_t color);
    Maze(float x, float y, color_t color, std::vector<std::vector<int>> &grid);
    glm::vec3 position;
    glm::vec3 initial_position;
    float rotation;
    int spin_axis;
    void draw(glm::mat4 VP);
    void draw();
    void move_position(glm::vec3 x);
    glm::vec3 get_position();
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

#endif // MAZE_H
