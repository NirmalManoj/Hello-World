#include "ball.h"
#include "main.h"

#define vt(tmp) tmp.x, tmp.y, tmp.z

Ball::Ball(float x, float y, color_t color) {
    srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    this->alive = true;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    glm::vec3 v1(-1.0f,-1.0f,-1.0f);
    glm::vec3 v2(-1.0f,-1.0f, 1.0f);
    glm::vec3 v3(-1.0f, 1.0f, 1.0f);
    
    static const GLfloat vertex_buffer_data[] = {
        vt(v1), // triangle 1 : begin
        vt(v2),
        vt(v3), // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    static GLfloat color_buffer_data[12*3*3];
    for(int i = 0; i < 12*3*3; i+=9)
    {
        color_buffer_data[i] = rand() % 256;
        color_buffer_data[i] /= 256.0;
        color_buffer_data[i] = rand() % 256;
        color_buffer_data[i] /= 256.0;
        for (int j = i+3; j < i + 9; j+=3){
            color_buffer_data[j] = color_buffer_data[i];
        }
        color_buffer_data[i+1] = rand() % 256;
        color_buffer_data[i+1] /= 256.0;
        for (int j = i+4; j < i + 9; j+=3){
            color_buffer_data[j] = color_buffer_data[i+1];
        }
        color_buffer_data[i+2] = rand() % 256;
        color_buffer_data[i+2] /= 256.0;
        for (int j = i+5; j < i + 9; j+=3){
            color_buffer_data[j] = color_buffer_data[i+2];
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color_buffer_data, GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
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
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

glm::vec3 Ball::get_position() {
    return this->position;
}


void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::move_position(glm::vec3 del){
    this->position = this->position + del;
}


void Ball::reset_position(){
    this->position = initial_position;
}

void Ball::start_spin()
{
    this->spin_axis = 1;
}
void Ball::stop_spin()
{
    this->spin_axis = 0;
}

float Ball::get_ang(float ang)
{
    return ang * M_PI / 180.0f;
}

void Ball::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bool Ball::is_live(){
    return this->alive;
}

void Ball::set_dead(){
    this->alive = false;
}
