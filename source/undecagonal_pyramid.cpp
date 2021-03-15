#include "undecagonal_pyramid.h"

#define vt(tmp) tmp.x, tmp.y, tmp.z
#define tri(tmp1, tmp2, tmp3) vt(tmp1), vt(tmp2), vt(tmp3)

UndecagonalPyramid::UndecagonalPyramid(float x, float y, color_t color)
{
    srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    speed = 1;

    // Vectors in decagon
    float reg_angle = 360.0 / 11.0f;
    glm::vec3 v1(cos(get_ang(0)), 0, sin(get_ang(0)));
    glm::vec3 v2(cos(get_ang(reg_angle * 1)), 0, sin(get_ang(reg_angle * 1)));
    glm::vec3 v3(cos(get_ang(reg_angle * 2)), 0, sin(get_ang(reg_angle * 2)));
    glm::vec3 v4(cos(get_ang(reg_angle * 3)), 0, sin(get_ang(reg_angle * 3)));
    glm::vec3 v5(cos(get_ang(reg_angle * 4)), 0, sin(get_ang(reg_angle * 4)));
    glm::vec3 v6(cos(get_ang(reg_angle * 5)), 0, sin(get_ang(reg_angle * 5)));
    glm::vec3 v7(cos(get_ang(reg_angle * 6)), 0, sin(get_ang(reg_angle * 6)));
    glm::vec3 v8(cos(get_ang(reg_angle * 7)), 0, sin(get_ang(reg_angle * 7)));
    glm::vec3 v9(cos(get_ang(reg_angle * 8)), 0, sin(get_ang(reg_angle * 8)));
    glm::vec3 v10(cos(get_ang(reg_angle * 9)), 0, sin(get_ang(reg_angle * 9)));
    glm::vec3 v11(cos(get_ang(reg_angle * 10)), 0, sin(get_ang(reg_angle * 10)));

    // Vectors that represent origin
    glm::vec3 vO(0, 0, 0);
    glm::vec3 vOT(0, 1, 0);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    //
    static const GLfloat vertex_buffer_data[] = {
        // Top side
        tri(v1, v2, vOT),   // Triangle 1
        tri(v2, v3, vOT),   // Triangle 2
        tri(v3, v4, vOT),   // Triangle 3
        tri(v4, v5, vOT),   // Triangle 4
        tri(v5, v6, vOT),   // Triangle 5
        tri(v6, v7, vOT),   // Triangle 6
        tri(v7, v8, vOT),   // Triangle 7
        tri(v8, v9, vOT),   // Triangle 8
        tri(v9, v10, vOT),  // Triangle 9
        tri(v10, v11, vOT), // Triangle 10
        tri(v11, v1, vOT),  // Triangle 11
        // Bottom side
        tri(v1, v2, vO),   // Triangle 12
        tri(v2, v3, vO),   // Triangle 13
        tri(v3, v4, vO),   // Triangle 14
        tri(v4, v5, vO),   // Triangle 15
        tri(v5, v6, vO),   // Triangle 16
        tri(v6, v7, vO),   // Triangle 17
        tri(v7, v8, vO),   // Triangle 18
        tri(v8, v9, vO),   // Triangle 19
        tri(v9, v10, vO),  // Triangle 20
        tri(v10, v11, vO), // Triangle 21
        tri(v11, v1, vO)   // Triangle 22
    };

    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    static GLfloat color_buffer_data[22 * 3 * 3];
    for (int i = 0; i < 11 * 3 * 3; i += 9)
    {
        color_buffer_data[i] = rand() % 256;
        color_buffer_data[i] /= 256.0;
        color_buffer_data[i] = rand() % 256;
        color_buffer_data[i] /= 256.0;
        for (int j = i + 3; j < i + 9; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i];
        }
        color_buffer_data[i + 1] = rand() % 256;
        color_buffer_data[i + 1] /= 256.0;
        for (int j = i + 4; j < i + 9; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 1];
        }
        color_buffer_data[i + 2] = rand() % 256;
        color_buffer_data[i + 2] /= 256.0;
        for (int j = i + 5; j < i + 9; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 2];
        }
    }
    // Bottom side
    for (int i = 11 * 3 * 3; i < 22 * 3 * 3; i += 11 * 3 * 3)
    {
        color_buffer_data[i] /= 256.0;
        for (int j = i + 3; j < i + 11 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i];
        }
        color_buffer_data[i + 1] = rand() % 256;
        color_buffer_data[i + 1] /= 256.0;
        for (int j = i + 4; j < i + 11 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 1];
        }
        color_buffer_data[i + 2] = rand() % 256;
        color_buffer_data[i + 2] /= 256.0;
        for (int j = i + 5; j < i + 11 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 2];
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 40 * 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}
