#include "maze.h"
#include "main.h"

#define vt(tmp) tmp.x, tmp.y, tmp.z

Maze::Maze(float x, float y, color_t color) {
    srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    glm::vec3 v1(-1, 1, 0);
    glm::vec3 v2(1, 1, 0);
    glm::vec3 v3(-1.0f, -1.0f, 0);
    glm::vec3 v4(1, -1.0f, 0);
    
    static const GLfloat vertex_buffer_data[] = {
        vt(v1), // Line 1 : begin
        vt(v2),
        vt(v1),
        vt(v3),
        vt(v2),
        vt(v4),
        vt(v3),
        vt(v4)
    };

    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    const int NO_VETIC = 4;
    static GLfloat color_buffer_data[NO_VETIC*2*3];
    for(int i = 0; i < NO_VETIC*2*3; i+=1)
    {
        color_buffer_data[i] = 123.9;
    }
    this->object = create3DObject(GL_LINES, NO_VETIC*3, vertex_buffer_data, color_buffer_data, GL_FILL);
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
