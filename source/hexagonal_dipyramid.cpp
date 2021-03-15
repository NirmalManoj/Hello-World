#include "hexagonal_dipyramid.h"

HexagonalDipyramid::HexagonalDipyramid(float x, float y, color_t color)
{
    srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
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
