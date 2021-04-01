#include "task.h"

#define vt(tmp) tmp.x, tmp.y, tmp.z
#define tri(tmp1, tmp2, tmp3) vt(tmp1), vt(tmp2), vt(tmp3)

Task::Task(float x, float y, color_t color)
{
    // srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    speed = 1;
    glm::vec3 v1(0, 0, 0);
    glm::vec3 v2(-0.04, -0.05, 0);
    glm::vec3 v3(0.04, -0.05, 0);
    glm::vec3 v4(0.04, 0.05, 0);
    glm::vec3 v5(-0.04, 0.05, 0);
    


    static const GLfloat vertex_buffer_data[] = {
        tri(v1, v2, v3),
        tri(v1, v4, v5)
    };

    const int NO_TRI = 2;
    std::cout << "NOT TIR: " << NO_TRI << "\n";
    static GLfloat color_buffer_data[100];
    for(int i = 0; i < NO_TRI*3*3; i+=3){
        color_buffer_data[i] = 139.0;
        color_buffer_data[i] /= 256.0;
        color_buffer_data[i+1] = 80.0;
        color_buffer_data[i+1] /= 256.0;
        color_buffer_data[i+2] = 242.0;
        color_buffer_data[i+2] /= 256.0;
    }
    // for(int i = 0; i < 2*3*3; i+=3)
    // {
    //     // Grey white
    //     color_buffer_data[i] = 255.9;
    //     color_buffer_data[i] /= 256.0;
    //     color_buffer_data[i+1] = 38.9;
    //     color_buffer_data[i+1] /= 256.0;
    //     color_buffer_data[i+2] = 0.9;
    //     color_buffer_data[i+2] /= 256.0;
    // }
    // for(int i = 4*3*3; i < 6*3*3; i+=3)
    // {
    //     // Big rectangle
    //     color_buffer_data[base_size*3+i] = 212.0;
    //     color_buffer_data[base_size*3+i] /= 256.0;
    //     color_buffer_data[base_size*3+i+1] = 235.0;
    //     color_buffer_data[base_size*3+i+1] /= 256.0;
    //     color_buffer_data[base_size*3+i+2] = 68.0;
    //     color_buffer_data[base_size*3+i+2] /= 256.0;
    // }
    // for(int i = 6*3*3; i < 8*3*3; i+=3)
    // {
    //     // Blue
    //     color_buffer_data[base_size*3+i] = 28.0;
    //     color_buffer_data[base_size*3+i] /= 256.0;
    //     color_buffer_data[base_size*3+i+1] = 4.0;
    //     color_buffer_data[base_size*3+i+1] /= 256.0;
    //     color_buffer_data[base_size*3+i+2] = 0.0;
    //     color_buffer_data[base_size*3+i+2] /= 256.0;
    // }
    // for(int i = 8*3*3; i < 10*3*3; i+=3)
    // {
    //     // Small box inside
    //     color_buffer_data[base_size*3+i] = 80.0;
    //     color_buffer_data[base_size*3+i] /= 256.0;
    //     color_buffer_data[base_size*3+i+1] = 131.0;
    //     color_buffer_data[base_size*3+i+1] /= 256.0;
    //     color_buffer_data[base_size*3+i+2] = 163.0;
    //     color_buffer_data[base_size*3+i+2] /= 256.0;
    // }
    this->object = create3DObject(GL_TRIANGLES, NO_TRI*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}