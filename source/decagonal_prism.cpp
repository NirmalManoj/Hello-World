#include "decagonal_prism.h"

#define vt(tmp) tmp.x, tmp.y, tmp.z
#define tri(tmp1, tmp2, tmp3) vt(tmp1), vt(tmp2), vt(tmp3)

DecagonalPrism::DecagonalPrism(float x, float y, color_t color)
{
    srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    speed = 1;

    // Vectors in decagon
    float heit = -0.8;
    glm::vec3 v1(cos(get_ang(0)), 0, sin(get_ang(0)));
    glm::vec3 v2(cos(get_ang(36 * 1)), 0, sin(get_ang(36 * 1)));
    glm::vec3 v3(cos(get_ang(36 * 2)), 0, sin(get_ang(36 * 2)));
    glm::vec3 v4(cos(get_ang(36 * 3)), 0, sin(get_ang(36 * 3)));
    glm::vec3 v5(cos(get_ang(36 * 4)), 0, sin(get_ang(36 * 4)));
    glm::vec3 v6(cos(get_ang(36 * 5)), 0, sin(get_ang(36 * 5)));
    glm::vec3 v7(cos(get_ang(36 * 6)), 0, sin(get_ang(36 * 6)));
    glm::vec3 v8(cos(get_ang(36 * 7)), 0, sin(get_ang(36 * 7)));
    glm::vec3 v9(cos(get_ang(36 * 8)), 0, sin(get_ang(36 * 8)));
    glm::vec3 v10(cos(get_ang(36 * 9)), 0, sin(get_ang(36 * 9)));

    glm::vec3 v11(cos(get_ang(0)), heit, sin(get_ang(0)));
    glm::vec3 v12(cos(get_ang(36 * 1)), heit, sin(get_ang(36 * 1)));
    glm::vec3 v13(cos(get_ang(36 * 2)), heit, sin(get_ang(36 * 2)));
    glm::vec3 v14(cos(get_ang(36 * 3)), heit, sin(get_ang(36 * 3)));
    glm::vec3 v15(cos(get_ang(36 * 4)), heit, sin(get_ang(36 * 4)));
    glm::vec3 v16(cos(get_ang(36 * 5)), heit, sin(get_ang(36 * 5)));
    glm::vec3 v17(cos(get_ang(36 * 6)), heit, sin(get_ang(36 * 6)));
    glm::vec3 v18(cos(get_ang(36 * 7)), heit, sin(get_ang(36 * 7)));
    glm::vec3 v19(cos(get_ang(36 * 8)), heit, sin(get_ang(36 * 8)));
    glm::vec3 v20(cos(get_ang(36 * 9)), heit, sin(get_ang(36 * 9)));

    // Vectors that represent origin
    glm::vec3 vO1(0, 0, 0);
    glm::vec3 vO2(0, heit, 0);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    //
    static const GLfloat vertex_buffer_data[] = {
        // Sides
        tri(v1, v2, v11),   // Triangle 1
        tri(v2, v11, v12),  // Triangle 2
        tri(v2, v3, v12),   // Triangle 3
        tri(v3, v12, v13),  // Triangle 4
        tri(v3, v4, v13),   // Triangle 5
        tri(v4, v13, v14),  // Triangle 6
        tri(v4, v5, v14),   // Triangle 7
        tri(v5, v14, v15),  // Triangle 8
        tri(v5, v6, v15),   // Triangle 9
        tri(v6, v15, v16),  // Triangle 10
        tri(v6, v7, v16),   // Triangle 11
        tri(v7, v16, v17),  // Triangle 12
        tri(v7, v8, v17),   // Triangle 13
        tri(v8, v17, v18),  // Triangle 14
        tri(v8, v9, v18),   // Triangle 15
        tri(v9, v18, v19),  // Triangle 16
        tri(v9, v10, v19),  // Triangle 17
        tri(v10, v19, v20), // Triangle 18
        tri(v10, v1, v20),  // Triangle 19
        tri(v1, v20, v11),  // Triangle 20
        // Top side
        tri(v1, v2, vO1),  // Triangle 21
        tri(v2, v3, vO1),  // Triangle 22
        tri(v3, v4, vO1),  // Triangle 23
        tri(v4, v5, vO1),  // Triangle 24
        tri(v5, v6, vO1),  // Triangle 25
        tri(v6, v7, vO1),  // Triangle 26
        tri(v7, v8, vO1),  // Triangle 27
        tri(v8, v9, vO1),  // Triangle 28
        tri(v9, v10, vO1), // Triangle 29
        tri(v10, v1, vO1), // Triangle 30
        // Bottom side
        tri(v11, v12, vO2), // Triangle 31
        tri(v12, v13, vO2), // Triangle 32
        tri(v13, v14, vO2), // Triangle 33
        tri(v14, v15, vO2), // Triangle 34
        tri(v15, v16, vO2), // Triangle 35
        tri(v16, v17, vO2), // Triangle 36
        tri(v17, v18, vO2), // Triangle 37
        tri(v18, v19, vO2), // Triangle 38
        tri(v19, v20, vO2), // Triangle 39
        tri(v20, v11, vO2), // Triangle 40
    };

    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    static GLfloat color_buffer_data[40 * 3 * 3];
    for (int i = 0; i < 20 * 3 * 3; i += 18)
    {
        // color_buffer_data[i] = rand() % 256;
        // color_buffer_data[i] /= 256.0;
        color_buffer_data[i] = rand() % 256;
        color_buffer_data[i] /= 256.0;
        for (int j = i + 3; j < i + 18; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i];
        }
        color_buffer_data[i + 1] = rand() % 256;
        color_buffer_data[i + 1] /= 256.0;
        for (int j = i + 4; j < i + 18; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 1];
        }
        color_buffer_data[i + 2] = rand() % 256;
        color_buffer_data[i + 2] /= 256.0;
        for (int j = i + 5; j < i + 18; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 2];
        }
    }
    // Top side
    for (int i = 20 * 3 * 3; i < 30 * 3 * 3; i += 10 * 3 * 3)
    {
        color_buffer_data[i] /= 256.0;
        for (int j = i + 3; j < i + 10 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i];
        }
        color_buffer_data[i + 1] = rand() % 256;
        color_buffer_data[i + 1] /= 256.0;
        for (int j = i + 4; j < i + 10 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 1];
        }
        color_buffer_data[i + 2] = rand() % 256;
        color_buffer_data[i + 2] /= 256.0;
        for (int j = i + 5; j < i + 10 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 2];
        }
    }
    // Bottom side
    for (int i = 30 * 3 * 3; i < 40 * 3 * 3; i += 10 * 3 * 3)
    {
        color_buffer_data[i] /= 256.0;
        for (int j = i + 3; j < i + 10 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i];
        }
        color_buffer_data[i + 1] = rand() % 256;
        color_buffer_data[i + 1] /= 256.0;
        for (int j = i + 4; j < i + 10 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 1];
        }
        color_buffer_data[i + 2] = rand() % 256;
        color_buffer_data[i + 2] /= 256.0;
        for (int j = i + 5; j < i + 10 * 3 * 3; j += 3)
        {
            color_buffer_data[j] = color_buffer_data[i + 2];
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 40 * 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}
