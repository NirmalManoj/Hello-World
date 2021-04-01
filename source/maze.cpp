#include "maze.h"
#include "main.h"
#include <vector>

#define vt(tmp) tmp.x, tmp.y, tmp.z

Maze::Maze(float x, float y, color_t color, std::vector<std::vector<int>> &grid){
    // srand(time(0)); 
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    this->height = grid.size();
    this->width = grid[0].size();//grid is never supposed to be empty

    this->top_left_x = -0.75f;
    this->top_left_y = 0.75f;
    // this->top_left_x = 0;
    // this->top_left_y = 0;
    this->unit_cell = 1.5/((float)height);

    
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // grid[0][0] = 4;
    // grid[0][1] = 10;
    // grid[1][0] = 4;
    // grid[1][1] = 9;
    std::vector<GLfloat> lines;
    std::cout << "GOING TO GENERATE top left: " << this->top_left_x << " top right: " << this->top_left_y << "\n";
    generate_maze(grid, lines);
    std::cout << "MAZE GENERATED\n";
    // glm::vec3 v1(-1, 1, 0);
    // glm::vec3 v2(1, 1, 0);
    // glm::vec3 v3(-1.0f, -1.0f, 0);
    // glm::vec3 v4(1, -1.0f, 0);
    
    // static const GLfloat vertex_buffer_data[] =   {
    //     vt(v1), // Line 1 : begin
    //     vt(v2),
    //     vt(v1),
    //     vt(v3),
    //     vt(v2),
    //     vt(v4),
    //     vt(v3),
    //     vt(v4)
    // };

    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    const int NO_VETIC = lines.size()/3;
    static GLfloat vertex_buffer_data[2000*3]; 
    for(int i = 0; i < lines.size(); i++){
        vertex_buffer_data[i] = lines[i];
    }

    static GLfloat color_buffer_data[2000*3];
    for(int i = 0; i < NO_VETIC*3; i+=3)
    {
        color_buffer_data[i] = 156.0;
        color_buffer_data[i] /= 256.0;
        color_buffer_data[i+1] = 149.0;
        color_buffer_data[i+1] /= 256.0;
        color_buffer_data[i+2] = 62.0;
        color_buffer_data[i+2] /= 256.0;
    }
    this->object = create3DObject(GL_LINES, NO_VETIC*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Maze::add_north_line(std::vector<GLfloat> &lines, int row, int col){
    float x = this->top_left_x + this->unit_cell * col;
    float y = this->top_left_y - this->unit_cell * row;
    glm::vec3 v1(x, y, 0);
    glm::vec3 v2(x+this->unit_cell, y, 0);
    std::cout << "At " << x << ", " << y << "\n";
    std::cout << row << " " << col << " =NN== " << v1.x << " " << v1.y << " to " << v2.x << " " << v2.y <<  "\n";
    lines.push_back(v1.x);
    lines.push_back(v1.y);
    lines.push_back(v1.z);
    lines.push_back(v2.x);
    lines.push_back(v2.y);
    lines.push_back(v2.z);
}

void Maze::add_south_line(std::vector<GLfloat> &lines, int row, int col){
    float x = this->top_left_x + this->unit_cell * col;
    float y = this->top_left_y - this->unit_cell * row;
    glm::vec3 v1(x, y-unit_cell, 0);
    glm::vec3 v2(x+unit_cell, y-unit_cell, 0);
    std::cout << "At " << x << ", " << y << "\n";
    std::cout << row << " " << col << " =SS== " << v1.x << " " << v1.y << " to " << v2.x << " " << v2.y <<  "\n";
    lines.push_back(v1.x);
    lines.push_back(v1.y);
    lines.push_back(v1.z);
    lines.push_back(v2.x);
    lines.push_back(v2.y);
    lines.push_back(v2.z);
}

void Maze::add_east_line(std::vector<GLfloat> &lines, int row, int col){
    float x = this->top_left_x + this->unit_cell * col;
    float y = this->top_left_y - this->unit_cell * row;
    // std::cout << row << " " << col << " =EE== " << x << " " << y << " to " << x+unit_cell << " " << y <<  "\n";
    // assert(1==2);
    glm::vec3 v1(x+unit_cell, y, 0);
    glm::vec3 v2(x+unit_cell, y-unit_cell, 0);
    std::cout << "At " << x << ", " << y << "\n";
    std::cout << row << " " << col << " =EE== " << v1.x << " " << v1.y << " to " << v2.x << " " << v2.y <<  "\n";
    lines.push_back(v1.x);
    lines.push_back(v1.y);
    lines.push_back(v1.z);
    lines.push_back(v2.x);
    lines.push_back(v2.y);
    lines.push_back(v2.z);
}

void Maze::add_west_line(std::vector<GLfloat> &lines, int row, int col){
    float x = this->top_left_x + this->unit_cell * col;
    float y = this->top_left_y - this->unit_cell * row;
    glm::vec3 v1(x, y, 0);
    glm::vec3 v2(x, y-unit_cell, 0);
    std::cout << "At " << x << ", " << y << "\n";
    std::cout << row << " " << col << " =WW== " << v1.x << " " << v1.y << " to " << v2.x << " " << v2.y <<  "\n";
    lines.push_back(v1.x);
    lines.push_back(v1.y);
    lines.push_back(v1.z);
    lines.push_back(v2.x);
    lines.push_back(v2.y);
    lines.push_back(v2.z);
}

void Maze::generate_maze(std::vector<std::vector<int>> &grid, std::vector<GLfloat> &lines){
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < grid[i].size(); j++){
            std::cout << grid[i][j] << " ";
            if ((grid[i][j] & 1) == 0){ // North
                add_north_line(lines, i, j);
            }
            if ((grid[i][j] & 2) == 0){ // South
                add_south_line(lines, i, j);
            }
            if ((grid[i][j] & 4) == 0){ // East
                if(i == 0 && j == 0){
                    // std::cout << "SSDPI\n";
                }
                add_east_line(lines, i, j);
            }
            if ((grid[i][j] & 8) == 0){ // West   
                add_west_line(lines, i, j);
            }
        }std::cout << "\n";
    }
}

void Maze::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate;
    if (spin_axis){
        rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    } else {
        rotate = glm::rotate((float)0.0, glm::vec3(1, 0, 0));
    }
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    // glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Maze::draw() {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
 
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= translate;
    glm::mat4 MVP = Matrices.model;
    // glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


glm::vec3 Maze::get_position() {
    return this->position;
}


void Maze::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Maze::move_position(glm::vec3 del){
    this->position = this->position + del;
}


void Maze::reset_position(){
    this->position = initial_position;
}

void Maze::start_spin()
{
    this->spin_axis = 1;
}
void Maze::stop_spin()
{
    this->spin_axis = 0;
}

float Maze::get_ang(float ang)
{
    return ang * M_PI / 180.0f;
}

void Maze::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
