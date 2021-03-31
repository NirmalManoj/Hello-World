#include "player.h"

#define vt(tmp) tmp.x, tmp.y, tmp.z
#define tri(tmp1, tmp2, tmp3) vt(tmp1), vt(tmp2), vt(tmp3)

Player::Player(float x, float y, color_t color)
{
    srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    speed = 1;

    // Vectors in decagon
    // float heit = -0.8;
    // glm::vec3 v1(cos(get_ang(0)), 0, sin(get_ang(0)));
    // glm::vec3 v2(cos(get_ang(36 * 1)), 0, sin(get_ang(36 * 1)));
    // glm::vec3 v3(cos(get_ang(36 * 2)), 0, sin(get_ang(36 * 2)));
    // glm::vec3 v4(cos(get_ang(36 * 3)), 0, sin(get_ang(36 * 3)));
    // glm::vec3 v5(cos(get_ang(36 * 4)), 0, sin(get_ang(36 * 4)));
    // glm::vec3 v6(cos(get_ang(36 * 5)), 0, sin(get_ang(36 * 5)));
    // glm::vec3 v7(cos(get_ang(36 * 6)), 0, sin(get_ang(36 * 6)));
    // glm::vec3 v8(cos(get_ang(36 * 7)), 0, sin(get_ang(36 * 7)));
    // glm::vec3 v9(cos(get_ang(36 * 8)), 0, sin(get_ang(36 * 8)));
    // glm::vec3 v10(cos(get_ang(36 * 9)), 0, sin(get_ang(36 * 9)));

    // glm::vec3 v11(cos(get_ang(0)), heit, sin(get_ang(0)));
    // glm::vec3 v12(cos(get_ang(36 * 1)), heit, sin(get_ang(36 * 1)));
    // glm::vec3 v13(cos(get_ang(36 * 2)), heit, sin(get_ang(36 * 2)));
    // glm::vec3 v14(cos(get_ang(36 * 3)), heit, sin(get_ang(36 * 3)));
    // glm::vec3 v15(cos(get_ang(36 * 4)), heit, sin(get_ang(36 * 4)));
    // glm::vec3 v16(cos(get_ang(36 * 5)), heit, sin(get_ang(36 * 5)));
    // glm::vec3 v17(cos(get_ang(36 * 6)), heit, sin(get_ang(36 * 6)));
    // glm::vec3 v18(cos(get_ang(36 * 7)), heit, sin(get_ang(36 * 7)));
    // glm::vec3 v19(cos(get_ang(36 * 8)), heit, sin(get_ang(36 * 8)));
    // glm::vec3 v20(cos(get_ang(36 * 9)), heit, sin(get_ang(36 * 9)));

    // // Vectors that represent origin
    // glm::vec3 vO1(0, 0, 0);
    // glm::vec3 vO2(0, heit, 0);
    
    // static const GLfloat vertex_buffer_data[] = {
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
    const float unit = 0.05f;
    glm::vec3 v1(-unit, unit, 0);
    glm::vec3 v2(unit, unit, 0);
    glm::vec3 v3(-unit, -unit, 0);
    glm::vec3 v4(unit, -unit, 0);
    
    static const GLfloat vertex_buffer_data[] = {
        tri(v1, v2, v3),
        tri(v2, v3, v4)
    };

    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    const int NO_VETIC = 4;
    static GLfloat color_buffer_data[NO_VETIC*3*3];
    for(int i = 0; i < NO_VETIC*3*3; i+=3)
    {
        color_buffer_data[i] = 150.9;
        color_buffer_data[i+1] = 190.9;
        color_buffer_data[i+2] = 240.9;
    }
    this->object = create3DObject(GL_TRIANGLES, NO_VETIC*3, vertex_buffer_data, color_buffer_data, GL_FILL);

}