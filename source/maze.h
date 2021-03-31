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

    void generate_maze(std::vector<std::vector<int>> &grid, std::vector<GLfloat> &lines);
    void add_north_line(std::vector<GLfloat> &lines, int row, int col);
    void add_south_line(std::vector<GLfloat> &lines, int row, int col);
    void add_east_line(std::vector<GLfloat> &lines, int row, int col);
    void add_west_line(std::vector<GLfloat> &lines, int row, int col);
    glm::vec3 position;
    glm::vec3 initial_position;
    float rotation;
    int spin_axis;
    int height;
    int width;
    float top_left_x;
    float top_left_y;
    float unit_cell;
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
