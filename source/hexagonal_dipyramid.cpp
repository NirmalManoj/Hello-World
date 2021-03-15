#include "hexagonal_dipyramid.h"

#define vt(tmp) tmp.x, tmp.y, tmp.z

HexagonalDipyramid::HexagonalDipyramid(float x, float y, color_t color)
{
    srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    speed = 1;

    // Vectors in hexagon
    glm::vec3 v1(cos(get_ang(0)), 0, sin(get_ang(0)));
    glm::vec3 v2(cos(get_ang(60)), 0, sin(get_ang(60)));
    glm::vec3 v3(cos(get_ang(120)), 0, sin(get_ang(120)));
    glm::vec3 v4(cos(get_ang(180)), 0, sin(get_ang(180)));
    glm::vec3 v5(cos(get_ang(240)), 0, sin(get_ang(240)));
    glm::vec3 v6(cos(get_ang(300)), 0, sin(get_ang(300)));

    // Vectors that represent height
    glm::vec3 v7(0, 0.5, 0);
    glm::vec3 v8(0, -0.5, 0);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        vt(v1), // triangle 1: begin
        vt(v2),
        vt(v7), // triangle 1: end
        vt(v2), // triangle 2: begin
        vt(v3),
        vt(v7), // triangle 2: end
        vt(v3), // triangle 3: begin
        vt(v4),
        vt(v7), // triangle 3: end
        vt(v4), // triangle 4: begin
        vt(v5),
        vt(v7), // triangle 4: end
        vt(v5), // triangle 5: begin
        vt(v6),
        vt(v7), // triangle 5: end
        vt(v6), // triangle 6: begin
        vt(v1),
        vt(v7), // triangle 6: end

        vt(v1), // triangle 7: begin
        vt(v2),
        vt(v8), // triangle 7: end
        vt(v2), // triangle 8: begin
        vt(v3),
        vt(v8), // triangle 8: end
        vt(v3), // triangle 9: begin
        vt(v4),
        vt(v8), // triangle 9: end
        vt(v4), // triangle 10: begin
        vt(v5),
        vt(v8), // triangle 10: end
        vt(v5), // triangle 11: begin
        vt(v6),
        vt(v8), // triangle 11: end
        vt(v6), // triangle 12: begin
        vt(v1),
        vt(v8) // triangle 12: end
    };

    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    static GLfloat color_buffer_data[12 * 3 * 3];
    for (int i = 0; i < 12 * 3 * 3; i += 9)
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
    this->object = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}
