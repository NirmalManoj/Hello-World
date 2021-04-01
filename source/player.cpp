#include "player.h"

#define vt(tmp) tmp.x, tmp.y, tmp.z
#define tri(tmp1, tmp2, tmp3) vt(tmp1), vt(tmp2), vt(tmp3)

Player::Player(float x, float y, color_t color)
{
    // srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->initial_position = this->position;
    this->rotation = 0;
    this->spin_axis = 0;
    this->game_over = false;
    speed = 1;

    this->health = 10;
    this->task_done = 0;
    this->time_left = 100;

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
    glm::vec3 v1(-unit, -unit, 0);
    glm::vec3 v2(-0.01, -unit, 0);
    glm::vec3 v3(-0.01, -unit+0.01, 0);
    glm::vec3 v4(-unit, -unit+0.01, 0);

    glm::vec3 v5(0.01, -unit, 0);
    glm::vec3 v6(unit, -unit, 0);
    glm::vec3 v7(unit, -unit+0.01, 0);
    glm::vec3 v8(0.01, -unit+0.01, 0);

    glm::vec3 v9(unit, unit-0.01, 0);
    glm::vec3 v10(-unit, unit-0.01, 0);

    glm::vec3 v11(-unit-0.01, -unit+0.015, 0);
    glm::vec3 v12(-unit-0.01, unit-0.015, 0);
    
    glm::vec3 v13(-0.025, unit-0.035, 0);
    glm::vec3 v14(0.025, unit-0.035, 0);
    glm::vec3 v15(0.025, unit-0.01, 0);
    glm::vec3 v16(-0.025, unit-0.01, 0);
    
    
    static const GLfloat vertex_buffer_data_tmp[] = {
        tri(v1, v2, v3),
        tri(v1, v3, v4),
        tri(v5, v8, v7),
        tri(v5, v6, v7),
        tri(v9, v10, v4),
        tri(v9, v7, v4),
        tri(v10, v11, v4),
        tri(v10, v11, v12),
        tri(v13, v14, v15),
        tri(v13, v15, v16)
    };

    static GLfloat vertex_buffer_data[1200*3];
    std::vector<GLfloat> trias;
    this->add_sector(trias);


    int base_size = trias.size();
    std::cout << "BASE SIZE: " << base_size << " " << base_size/3 << "\n";
    for(int i = 0; i < base_size; i++){
        vertex_buffer_data[i] = trias[i];
    }
    for(int i = 0; i < 10*3*3; i++){
        vertex_buffer_data[base_size+i] = vertex_buffer_data_tmp[i];
    }
    // this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    const int NO_TRI = 10+base_size/3;
    std::cout << "NOT TIR: " << NO_TRI << "\n";
    static GLfloat color_buffer_data[1200*3*3];
    base_size/=3;
    for(int i = 0; i < base_size*3; i+=3){
        color_buffer_data[i] = 224.9;
        color_buffer_data[i] /= 256.0;
        color_buffer_data[i+1] = 29.9;
        color_buffer_data[i+1] /= 256.0;
        color_buffer_data[i+2] = 156.9;
        color_buffer_data[i+2] /= 256.0;
    }
    for(int i = 0; i < 4*3*3; i+=3)
    {
        // Grey white
        color_buffer_data[base_size*3+i] = 212.9;
        color_buffer_data[base_size*3+i] /= 256.0;
        color_buffer_data[base_size*3+i+1] = 193.9;
        color_buffer_data[base_size*3+i+1] /= 256.0;
        color_buffer_data[base_size*3+i+2] = 108.9;
        color_buffer_data[base_size*3+i+2] /= 256.0;
    }
    for(int i = 4*3*3; i < 6*3*3; i+=3)
    {
        // Green
        color_buffer_data[base_size*3+i] = 19.0;
        color_buffer_data[base_size*3+i] /= 256.0;
        color_buffer_data[base_size*3+i+1] = 214.0;
        color_buffer_data[base_size*3+i+1] /= 256.0;
        color_buffer_data[base_size*3+i+2] = 52.0;
        color_buffer_data[base_size*3+i+2] /= 256.0;
    }
    for(int i = 6*3*3; i < 8*3*3; i+=3)
    {
        // Blue
        color_buffer_data[base_size*3+i] = 35.0;
        color_buffer_data[base_size*3+i] /= 256.0;
        color_buffer_data[base_size*3+i+1] = 180.0;
        color_buffer_data[base_size*3+i+1] /= 256.0;
        color_buffer_data[base_size*3+i+2] = 252.0;
        color_buffer_data[base_size*3+i+2] /= 256.0;
    }
    for(int i = 8*3*3; i < 10*3*3; i+=3)
    {
        // Green
        color_buffer_data[base_size*3+i] = 0.0;
        color_buffer_data[base_size*3+i] /= 256.0;
        color_buffer_data[base_size*3+i+1] = 158.0;
        color_buffer_data[base_size*3+i+1] /= 256.0;
        color_buffer_data[base_size*3+i+2] = 201.0;
        color_buffer_data[base_size*3+i+2] /= 256.0;
    }
    this->object = create3DObject(GL_TRIANGLES, NO_TRI*3, vertex_buffer_data, color_buffer_data, GL_FILL);

}

void Player::add_sector(std::vector<GLfloat> &trias){
    float x = -0.05;
    float y = 0.04;
    float radius = sqrt(x*x + y*y);
    std::cout << "RADIUS: " << radius << "\n";
    std::vector<GLfloat> vertx;
    for(x = -0.05f; x < 0.05f; x += 0.01f) {
        y = sqrt(radius*radius - x*x);
        vertx.push_back(x);
        vertx.push_back(y);
    }
    for(int i = 3; i < vertx.size(); i+=2){
        // Origin
        trias.push_back(0);
        trias.push_back(0);
        trias.push_back(0);
        // Previous point
        trias.push_back(vertx[i-3]);
        trias.push_back(vertx[i-2]);
        trias.push_back(0);
        // Current point
        trias.push_back(vertx[i-1]);
        trias.push_back(vertx[i]);
        trias.push_back(0);
    }
}

void Player::get_pos(int &row, int &col){
    col = round((this->position.x+0.675f)/0.15f);
    row = round((-this->position.y+0.675f)/0.15f);
}

void Player::set_game_over(bool win_status){
    this->game_over = true;
    this->won = win_status;
}

bool Player::is_game_over(){
    return this->game_over;
}

bool Player::is_won(){
    return this->won;
}

void Player::add_health(int x){
    this->health = this->health + x;
}

void Player::dec_health(int x){
    this->health = this->health - x;
    std::cout << "HI:: " << this->health << "\n";
    if (this->health < 0){
        this->set_game_over();
    }
}

void Player::add_task(){
    this->task_done = this->task_done + 1;
}

void Player::dec_time(){
    this->time_left = this->time_left - 1;
    if (this->time_left <= 0){
        this->set_game_over();
    }
}

int Player::get_health(){
    return this->health;
}

int Player::get_task_done(){
    return this->task_done;
}

int Player::get_time(){
    return this->time_left;
}
