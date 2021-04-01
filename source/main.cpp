#include "main.h"
#include "timer.h"
#include "ball.h"
#include "hexagonal_dipyramid.h"
#include "decagonal_prism.h"
#include "undecagonal_pyramid.h"
#include "maze.h"
#include "player.h"
#include "enemy.h"
#include "vaporizer.h"
#include "task.h"
#include "button.h"
#include "bomb.h"
#include "coin.h"
#include <string>
#include <vector>
#include <algorithm>
#include <random>
// shuffle algorithm example
#include <iostream>  // std::cout
#include <algorithm> // std::shuffle
#include <vector>    // std::vector
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock
#include <map>
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);
/// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};
std::map<GLchar, Character> Characters;
unsigned int text_VAO, text_VBO;

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

const int N = 1;
const int S = 2;
const int E = 4;
const int W = 8;
// int dx[] = {1, -1, 0, 0};
// int dy[] = {0, 0, -1, 1};
//  E, W,  N, S

map<int, int> dx;
map<int, int> dy;
map<int, int> opposite;
vector<vector<int>> maze_layout;
// dx[E]=1;dx[W]=-1;dx[N]=0;dx[S]=0;
// dx[E]=1;dx[W]=-1;dx[N]=0;dx[S]=0;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine e(seed);

/**************************
* Customizable functions *
**************************/
Ball ball1;
Player player1; // Player
// Maze
Maze maze1;
// Ball maze1;
Enemy enemy1;
Vaporizer vaporizer1;
Task task1[2];
Button button1;
std::vector<Bomb> bomb1;
std::vector<Coin> coin1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

int camera_spot = 1;
int should_rotate = 0;

int select_model = 0;
// Eye - Location of camera. Don't change unless you are sure!!
// glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
glm::vec3 eye(1, 1, 1);
// Target - Where is the camera looking at.  Don't change unless you are sure!!
glm::vec3 target(0, 0, 0);
// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
glm::vec3 up(0, 1, 0);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye(0, 0, 0.75);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target(0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up(0, 1, 0);

    // const float radius = 3.0f;
    // float camX = sin(glfwGetTime()) * radius;
    // float camZ = cos(glfwGetTime()) * radius;
    // // glm::mat4 view;
    // if (should_rotate){
    //     if (camera_spot != 0 || true){
    //         eye = glm::vec3(camX, 0.7, camZ);
    //         target = glm::vec3(0.0, 0.0, 0.0);
    //         up = glm::vec3(0.0, 1.0, 0.1);
    //     }
    //     Matrices.view = glm::lookAt( eye, target, up );
    // } else {
    //     // eye = glm::vec3(1, 1, 1);
    //     // target = glm::vec3(0, 0, 0);
    //     // up = glm::vec3(0, 1, 0);
    //     if (camera_spot == 1 ){
    //         eye = glm::vec3(0, 0, 3);
    //         // target = ball1.get_position();
    //         up = glm::vec3(0, 1, 0);
    //         Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    //     } else if (camera_spot == 2){
    //         eye = glm::vec3(1, 0.5, 1);
    //         // target = ball1.get_position();
    //         up = glm::vec3(0, 1, 0);
    //         Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    //     } else if (camera_spot == 3){
    //         eye = glm::vec3(0, 2, 3);
    //         // target = ball1.get_position();
    //         up = glm::vec3(0, 1, 0);
    //         Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    //     } else if (camera_spot == 0) {
    //         Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    //     }
    // }
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, target, up); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render
    // maze1.draw();
    // cout << "HI1\n";

    if(player1.is_game_over()){
        return;
    }

    maze1.draw(VP);
    player1.draw(VP);
    if (enemy1.is_live()){
        enemy1.draw(VP);
        vaporizer1.draw(VP);
    }
    for(int i = 0; i < 2; i++){
        if(task1[i].is_live()){
            task1[i].draw(VP);
        }
    }
    if (button1.is_live()){
        button1.draw(VP);
    }
    for(int i = 0; i < bomb1.size(); i++){
        if(bomb1[i].is_live()==false){
            continue;
        }
        bomb1[i].draw(VP);
    }
    for(int i = 0; i < coin1.size(); i++){
        if(coin1[i].is_live()==false){
            continue;
        }
        coin1[i].draw(VP);
    }
    // maze1.draw();
    // cout << "HI2\n";
}

void move_north()
{
    glm::vec3 tmp = player1.get_position();
    int row = ((tmp.x + 0.675f) / 0.15f);
    int col = ((-tmp.y + 0.675f) / 0.15f);
    swap(row, col);
    cout << "North from: " << row << " " << col << " |||| " << maze_layout[row][col] << "\n";
    float unit = 0.15f;
    if ((maze_layout[row][col] & N) == N)
    {
        player1.set_position(tmp.x, tmp.y + unit);
    }
}

void move_south()
{
    glm::vec3 tmp = player1.get_position();
    int row = ((tmp.x + 0.675f) / 0.15f);
    int col = ((-tmp.y + 0.675f) / 0.15f);
    swap(row, col);
    cout << "South from: " << row << " " << col << " |||| " << maze_layout[row][col] << "\n";
    float unit = 0.15f;
    if ((maze_layout[row][col] & S) == S)
    {
        player1.set_position(tmp.x, tmp.y - unit);
    }
}

void move_east()
{
    glm::vec3 tmp = player1.get_position();
    int row = ((tmp.x + 0.675f) / 0.15f);
    int col = ((-tmp.y + 0.675f) / 0.15f);
    swap(row, col);
    cout << "East from: " << row << " " << col << " |||| " << maze_layout[row][col] << "\n";
    float unit = 0.15f;
    if (row == 9 && col == 9){
        if(player1.get_task_done() == 2){
            player1.set_game_over(true);
        }
        return;
    }
    if ((maze_layout[row][col] & E) == E)
    {
        player1.set_position(tmp.x + unit, tmp.y);
    }
}

void move_west()
{
    glm::vec3 tmp = player1.get_position();
    int row = ((tmp.x + 0.675f) / 0.15f);
    int col = ((-tmp.y + 0.675f) / 0.15f);
    swap(row, col);
    cout << "West from: " << row << " " << col << " |||| " << maze_layout[row][col] << "\n";
    float unit = 0.15f;
    if ((maze_layout[row][col] & W) == W)
    {
        player1.set_position(tmp.x - unit, tmp.y);
    }
}

void tick_input(GLFWwindow *window)
{
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int start_spin_ = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
    int stop_spin_ = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
    int cam1 = glfwGetKey(window, GLFW_KEY_F7);
    int cam2 = glfwGetKey(window, GLFW_KEY_F8);
    int cam3 = glfwGetKey(window, GLFW_KEY_F9);

    int start_rotate = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
    int stop_rotate = glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL);

    int key_w = glfwGetKey(window, GLFW_KEY_W);
    int key_a = glfwGetKey(window, GLFW_KEY_A);
    int key_s = glfwGetKey(window, GLFW_KEY_S);
    int key_d = glfwGetKey(window, GLFW_KEY_D);
    int key_e = glfwGetKey(window, GLFW_KEY_E);
    int key_r = glfwGetKey(window, GLFW_KEY_R);

    int key_i = glfwGetKey(window, GLFW_KEY_I);
    int key_j = glfwGetKey(window, GLFW_KEY_J);
    int key_k = glfwGetKey(window, GLFW_KEY_K);
    int key_l = glfwGetKey(window, GLFW_KEY_L);
    int key_o = glfwGetKey(window, GLFW_KEY_O);
    int key_p = glfwGetKey(window, GLFW_KEY_P);

    int key_t = glfwGetKey(window, GLFW_KEY_T);


    if (key_t){
        int row1, col1, row2, col2;
        player1.get_pos(row2, col2);
        for(int i = 0; i < 2; i++){
            if(task1[i].is_live() == false){
                continue;
            }
            task1[i].get_pos(row1, col1);
            if(row1 == row2 && col1 == col2){
                task1[i].set_dead();
                player1.add_task();
                player1.add_health(10);
            }
        }
    }

    const float camera_speed = 0.05f;
    if (key_w && t60.processMove())
    {
        // camera_spot = 0;
        // eye += camera_speed * cameraFront;
        // target += camera_speed * cameraFront;
        move_north();
    }
    if (key_s && t60.processMove())
    {
        //     camera_spot = 0;
        //     eye -= camera_speed * cameraFront;
        //     target -= camera_speed * cameraFront;
        move_south();
    }
    if (key_a && t60.processMove())
    {
        // camera_spot = 0;
        // eye -= camera_speed * glm::vec3(1, 0, 0);
        // target -= camera_speed * glm::vec3(1, 0, 0);
        move_west();
    }
    if (key_d && t60.processMove())
    {
        // camera_spot = 0;
        // eye += camera_speed * glm::vec3(1, 0, 0);
        // target += camera_speed * glm::vec3(1, 0, 0);
        move_east();
    }

    // if (key_e) {
    //     camera_spot = 0;
    //     eye += camera_speed * glm::vec3(0, 1, 0);
    //     target += camera_speed * glm::vec3(0, 1, 0);
    // }

    // if (key_r) {
    //     camera_spot = 0;
    //     eye -= camera_speed * glm::vec3(0, 1, 0);
    //     target -= camera_speed * glm::vec3(0, 1, 0);
    // }

    // if (key_i){
    //     ball1.move_position(cameraFront*camera_speed);
    // }
    if (key_k){ // Cheat
        enemy1.set_dead();
    }
    // if (key_j){
    //     ball1.move_position(-1.0f*glm::vec3(1, 0, 0)*camera_speed);
    // }
    // if (key_l){
    //     ball1.move_position(1.0f*glm::vec3(1, 0, 0)*camera_s peed);
    // }
    if (key_o){ // Cheat
        player1.set_game_over(); // "Game over lise"
    }
    if (key_p){ // Cheat
        player1.set_game_over(true); // "Game over win"
    }

    // if (start_rotate){
    //     ball1.reset_position();
    //     camera_spot = 1;
    //     should_rotate = 1;
    // }
    // if (stop_rotate) {
    //     should_rotate = 0;
    // }
    // if (left) {
    //     // Do something
    //     should_rotate = 1 - should_rotate;
    // }
    // if (start_spin_) {
    //     // Spin object around an axis
    //     ball1.start_spin();
    // }
    // if (stop_spin_) {
    //     ball1.stop_spin();
    // }
    // if (cam1){
    //     // ball1.reset_position();
    //         target = ball1.get_position();
    //     camera_spot = 1;
    // }
    // if (cam2){
    //     // ball1.reset_position();
    //         target = ball1.get_position();
    //     camera_spot = 2;
    // }
    // if (cam3){
    //     // ball1.reset_position();
    //         target = ball1.get_position();
    //     camera_spot = 3;
    // }
}

// bool edge_exists(int node1, int node2){
//     int row1 = node1 / 10;
//     int col1 = node1 % 10;
//     int row2 = node2 / 10;
//     int col2 = node2 % 10;
// }

void move_enemy()
{
    if(enemy1.is_live() == false){
        return;
    }
    int row1, col1; // player
    int row2, col2; // enemy
    player1.get_pos(row1, col1);
    enemy1.get_pos(row2, col2);
    std::cout << row1 << " " << col1 << "   " << row2 << " " << col2 << "\n";
    // assert(1==2);
    const int total_no_of_vertices = 200;
    int dist[total_no_of_vertices][total_no_of_vertices];
    int next[total_no_of_vertices][total_no_of_vertices];
    for (int i = 0; i < total_no_of_vertices; i++)
    {
        for (int j = 0; j < total_no_of_vertices; j++)
        {
            dist[i][j] = 121312321;
            next[i][j] = -1;
        }
        next[i][i] = 0;
        dist[i][i] = 0;
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int node1 = i * 10 + j;
            int node2;
            if ((maze_layout[i][j] & N) == N)
            {
                node2 = node1 - 10;
                dist[node1][node2] = 1;
                next[node1][node2] = N;
            }
            if ((maze_layout[i][j] & S) == S)
            {
                node2 = node1 + 10;
                dist[node1][node2] = 1;
                next[node1][node2] = S;
            }
            if ((maze_layout[i][j] & E) == E)
            {
                node2 = node1 + 1;
                dist[node1][node2] = 1;
                next[node1][node2] = E;
            }
            if ((maze_layout[i][j] & W) == W)
            {
                node2 = node1 - 1;
                dist[node1][node2] = 1;
                next[node1][node2] = W;
            }
        }
    }
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    int nxt = next[row2 * 10 + col2][row1 * 10 + col1];
    float unit = 0.15f;
    glm::vec3 tmp = enemy1.get_position();
    if (nxt == N)
    {
        std::cout << "Moving north\n";
        enemy1.set_position(tmp.x, tmp.y + unit);
    }
    if (nxt == S)
    {
        std::cout << "Moving south\n";
        enemy1.set_position(tmp.x, tmp.y - unit);
    }
    if (nxt == E)
    {
        std::cout << "Moving east\n";
        enemy1.set_position(tmp.x + unit, tmp.y);
    }
    if (nxt == W)
    {
        std::cout << "Moving west\n";
        enemy1.set_position(tmp.x - unit, tmp.y);
    }
}

void check_vaporizer_collision(){
    if(vaporizer1.is_live() == false){
        return;
    }
    int row1, col1, row2, col2;
    player1.get_pos(row1, col1);
    vaporizer1.get_pos(row2, col2);
    if(row1 == row2 && col1 == col2){
        vaporizer1.set_dead();
        player1.add_health(5);
        enemy1.set_dead();
    }
}

void check_enemy_collision() {
    if(enemy1.is_live() == false){
        return;
    }
    int row1, col1, row2, col2;
    player1.get_pos(row1, col1);
    enemy1.get_pos(row2, col2);
    if(row1 == row2 && col1 == col2){
        player1.set_game_over(false);// Enemy - collision temp disabled
    }
}

void check_button_collision(){
    if(button1.is_live() == false){
        return;
    }
    int row1, col1, row2, col2, row_no, col_no;
    player1.get_pos(row1, col1);
    button1.get_pos(row2, col2);
    if(row1 == row2 && col1 == col2){
        button1.set_dead();
        // Insert the obstacles and powerups here!
        for(int i = 0; i < 4; i++){
            row_no = rand() % 10;   
            col_no = rand() % 10;
            bomb1.push_back(Bomb(-0.675f+col_no*0.15f, 0.675f - row_no*0.15, COLOR_GREEN));
        }
        for(int i = 0; i < 7; i++){
            row_no = rand() % 10;   
            col_no = rand() % 10;
            coin1.push_back(Coin(-0.675f+col_no*0.15f, 0.675f - row_no*0.15, COLOR_GREEN));
        }
    }
}

void check_bomb_collision(){
    for(int i = 0; i < bomb1.size(); i++){
        if(bomb1[i].is_live() == false){
            continue;
        }
        int row1, col1, row2, col2, row_no, col_no;
        player1.get_pos(row1, col1);
        bomb1[i].get_pos(row2, col2);
        // std::cout << row2 << " " << col2 << " That's it.\n";
        if(row1 == row2 && col1 == col2 && bomb1[i].is_live()){
            bomb1[i].set_dead();
            player1.dec_health(5);
        }
    }
}


void check_coin_collision(){
    for(int i = 0; i < coin1.size(); i++){
        if(coin1[i].is_live() == false){
            continue;
        }
        int row1, col1, row2, col2, row_no, col_no;
        player1.get_pos(row1, col1);
        coin1[i].get_pos(row2, col2);
        // std::cout << row2 << " " << col2 << " That's it.\n";
        if(row1 == row2 && col1 == col2 && coin1[i].is_live()){
            coin1[i].set_dead();
            player1.add_health(5);
        }
    }
}

void tick_elements()
{
    // ball1.tick();
    // camera_rotation_angle += 1;
    maze1.tick();
    if (t60.moveEnemy())
    {
        // enemy1.move_position();
        move_enemy();
    }
    if(t60.processSecond()){
        player1.dec_time();
    }
    check_vaporizer_collision();
    check_enemy_collision();
    check_button_collision();
    check_bomb_collision();
    check_coin_collision();
}   

void chooseModel()
{
    // srand(time(0));
    
    if (select_model == 0)
    {
        // ball1 = Ball(0, 0, COLOR_GREEN);
        // ball1 = HexagonalDipyramid(-0.675f, 0.675f, COLOR_GREEN);
        player1 = Player(-0.675f, 0.675f, COLOR_GREEN);
        maze1 = Maze(0, 0, COLOR_GREEN, maze_layout);
        // enemy1 = Enemy(0.675f, -0.675f, COLOR_GREEN);
        // int cell_no = rand() % 100;
        int row_no = rand() % 5;
        int col_no = rand() % 5;
        row_no += 5;
        col_no += 5;
        enemy1 = Enemy(-0.675f+col_no*0.15f, 0.675f - row_no*0.15, COLOR_GREEN);
        row_no = rand() % 10;   
        col_no = rand() % 10;
        vaporizer1 = Vaporizer(-0.675f+col_no*0.15f, 0.675f - row_no*0.15, COLOR_GREEN);
        std::cout << "ROW: " << row_no << "  COL: " << col_no << "\n";
        for(int i = 0; i < 2; i++){
            row_no = rand() % 10;   
            col_no = rand() % 10;
            task1[i] = Task(-0.675f+col_no*0.15f, 0.675f - row_no*0.15, COLOR_GREEN);
            std::cout << "ROW: " << row_no << "  COL: " << col_no << "\n";
        }
        // assert(1==2);
        row_no = rand() % 10;   
        col_no = rand() % 10;
        button1 = Button(-0.675f+col_no*0.15f, 0.675f - row_no*0.15, COLOR_GREEN);
    }
    else if (select_model == 1)
    {
        ball1 = HexagonalDipyramid(0, 0, COLOR_GREEN);
    }
    else if (select_model == 2)
    {
        ball1 = DecagonalPrism(0, 0, COLOR_GREEN);
    }
    else if (select_model == 3)
    {
        ball1 = UndecagonalPyramid(0, 0, COLOR_GREEN);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    chooseModel();

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv)
{
    srand(time(0));
    // His directions
    // dx[E]=1;dx[W]=-1;dx[N]=0;dx[S]=0;
    // dy[E]=0;dy[W]=0;dy[N]=-1;dy[S]=1;
    // My rewriting
    dx[E] = 0;
    dx[W] = 0;
    dx[N] = -1;
    dx[S] = 1;
    dy[E] = 1;
    dy[W] = -1;
    dy[N] = 0;
    dy[S] = 0;
    opposite[E] = W;
    opposite[W] = E;
    opposite[N] = S;
    opposite[S] = N;
    make_maze(10, 10);
    maze_layout[9][9] |= E;
    //     for(int i = 0; i < 10; i++){
    //     for(int j = 0; j < 10; j++){
    //         cout << maze_layout[i][j] << " ";
    //     }cout << "\n";
    // }
    // return 0;
    // if (argc >= 2) {
    //     // cerr << "Hello: " << argv[1] << "\n\n\n";
    //     select_model = stoi(argv[1]);
    // } else {
    //     cout << "Models available:\n";
    //     cout << "1. Hexagonal Dipyramid.\n";
    //     cout << "2. Decagonal Prism.\n";
    //     cout << "3. Undecagonal Pyramid.\n";
    //     cout << "Please enter the model number you want to choose: ";
    //     cin >> select_model;
    //     if (select_model < 1 || select_model > 3) {
    //         select_model = 2;
    //         cout << "You have entered an incorrect model number, so going with Decagonal Prism.\n";
    //     }
    // }

    int width = 1800;
    int height = 1000;

    window = initGLFW(width, height);

    initGL(window, width, height);

    // compile and setup the shader
    // ----------------------------
    Shader shader("../source/shaders/text.vert", "../source/shaders/text.frag");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "../source/Antonio-Bold.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x};
        Characters.insert(std::pair<char, Character>(c, character));
    }

    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // configure text_VAO/text_VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &text_VAO);
    glGenBuffers(1, &text_VBO);
    glBindVertexArray(text_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    char game_title[123];
    char HUD[123];
    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glfwSwapBuffers(window);
        // glfwPollEvents();
        // Boiler below

        // Process timers

        if (t60.processTick())
        {
            if (player1.is_game_over()){
                draw();
                glEnable(GL_CULL_FACE);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                RenderText(shader, "Game over!", 740.0f, 600.0f, 1.65f, glm::vec3(0.91f, 0.82f, 0.0756f));
                if(player1.is_won()) {
                    RenderText(shader, "Cheers! You won this game :)", 650.0f, 500.0f, 1.1f, glm::vec3(0.0f, 0.9f, 0.0f));
                }
                else {
                    RenderText(shader, "OOops!! You lost :p", 710.0f, 500.0f, 1.1f, glm::vec3(1.0f, 0.0f, 0.0f));
                }

                RenderText(shader, "Press Q to exit the game.", 700.0f, 400.0f, 0.5f, glm::vec3(0.1132, 0.003, 0.160f));
                glDisable(GL_CULL_FACE);
                glDisable(GL_BLEND);   
                glfwSwapBuffers(window);
            } else {
                sprintf(game_title, "AMONG US");
                sprintf(HUD, "Health: %d, Tasks done: %d/2, Time left: %ds, Light: On", player1.get_health(), player1.get_task_done(), player1.get_time());
                draw();

                glEnable(GL_CULL_FACE);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                // Heads up display
                RenderText(shader, HUD, 670.0f, 900.0f, 0.5f, glm::vec3(0.988f, 0.371f, 0.0f));
                RenderText(shader, game_title, 830.0f, 950.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

                glDisable(GL_CULL_FACE);
                glDisable(GL_BLEND);


                // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);

                tick_elements();
                tick_input(window);

            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen()
{
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void carve_passages_from(int cx, int cy, vector<vector<int>> &grid)
{
    vector<int> dir;
    dir.push_back(N);
    dir.push_back(S);
    dir.push_back(E);
    dir.push_back(W);
    shuffle(dir.begin(), dir.end(), e);
    for (auto direction : dir)
    {
        int nx = cx + dx[direction];
        int ny = cy + dy[direction];
        if (0 <= nx && nx < grid.size() && 0 <= ny && ny < grid[nx].size() && grid[nx][ny] == 0)
        {
            grid[cx][cy] |= direction;
            grid[nx][ny] |= opposite[direction];
            carve_passages_from(nx, ny, grid); // Probably buggy
        }
    }
}

void make_maze(int height, int width)
{
    vector<int> dir;
    dir.push_back(N);
    dir.push_back(S);
    dir.push_back(E);
    dir.push_back(W);
    vector<vector<int>> grid(height, vector<int>(width, 0));
    carve_passages_from(0, 0, grid);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    maze_layout = vector<vector<int>>(grid.begin(), grid.end());
}

// render line of text
// -------------------
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_VAO);
    // std::cout << "TO PRINT: " << text << "\n";
    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}