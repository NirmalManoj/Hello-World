#include "main.h"
#include "timer.h"
#include "ball.h"
#include "hexagonal_dipyramid.h"
#include "decagonal_prism.h"
#include "undecagonal_pyramid.h"
#include <string>
#include <vector>
#include <algorithm>
#include <random>
// shuffle algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <vector>       // std::vector
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

int camera_spot = 1;
int should_rotate = 0;

int select_model = 0;
// Eye - Location of camera. Don't change unless you are sure!!
// glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
glm::vec3 eye (1, 1, 1);
// Target - Where is the camera looking at.  Don't change unless you are sure!!
glm::vec3 target (0, 0, 0);
// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
glm::vec3 up (0, 1, 0);
glm::vec3 cameraFront (0.0f, 0.0f, -1.0f);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // // Eye - Location of camera. Don't change unless you are sure!!
    // // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // glm::vec3 eye (1, 1, 1);
    // // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);


    const float radius = 3.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    // glm::mat4 view;
    if (should_rotate){
        if (camera_spot != 0 || true){
            eye = glm::vec3(camX, 0.7, camZ);
            target = glm::vec3(0.0, 0.0, 0.0);
            up = glm::vec3(0.0, 1.0, 0.1);
        }
        Matrices.view = glm::lookAt( eye, target, up );
    } else {
        // eye = glm::vec3(1, 1, 1);
        // target = glm::vec3(0, 0, 0);
        // up = glm::vec3(0, 1, 0);
        if (camera_spot == 1 ){
            eye = glm::vec3(0, 0, 3);
            // target = ball1.get_position();
            up = glm::vec3(0, 1, 0);
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
        } else if (camera_spot == 2){
            eye = glm::vec3(1, 0.5, 1);
            // target = ball1.get_position();
            up = glm::vec3(0, 1, 0);
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
        } else if (camera_spot == 3){
            eye = glm::vec3(0, 2, 3);
            // target = ball1.get_position();
            up = glm::vec3(0, 1, 0);
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
        } else if (camera_spot == 0) {
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
        }
    }
      

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
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

    const float camera_speed = 0.05f;
    if (key_w) {
        camera_spot = 0;
        eye += camera_speed * cameraFront;
        target += camera_speed * cameraFront;
    }
    if (key_s) {
        camera_spot = 0;
        eye -= camera_speed * cameraFront;
        target -= camera_speed * cameraFront;

    }
    if (key_a) {
        camera_spot = 0;
        eye -= camera_speed * glm::vec3(1, 0, 0);
        target -= camera_speed * glm::vec3(1, 0, 0);
    }
    if (key_d) {
        camera_spot = 0;
        eye += camera_speed * glm::vec3(1, 0, 0);
        target += camera_speed * glm::vec3(1, 0, 0);
    }

    if (key_e) {
        camera_spot = 0;
        eye += camera_speed * glm::vec3(0, 1, 0);
        target += camera_speed * glm::vec3(0, 1, 0);
    }

    if (key_r) {
        camera_spot = 0;
        eye -= camera_speed * glm::vec3(0, 1, 0);
        target -= camera_speed * glm::vec3(0, 1, 0);
    }

    if (key_i){
        ball1.move_position(cameraFront*camera_speed);
    }
    if (key_k){
        ball1.move_position(-1.0f*cameraFront*camera_speed);
    }
    if (key_j){
        ball1.move_position(-1.0f*glm::vec3(1, 0, 0)*camera_speed);
    }
    if (key_l){
        ball1.move_position(1.0f*glm::vec3(1, 0, 0)*camera_speed);
    }
    if (key_o){
        ball1.move_position(1.0f*glm::vec3(0, 1, 0)*camera_speed);
    }
    if (key_p){
        ball1.move_position(-1.0f*glm::vec3(0, 1, 0)*camera_speed);
    }

    if (start_rotate){
        ball1.reset_position();
        camera_spot = 1;
        should_rotate = 1;
    }
    if (stop_rotate) {
        should_rotate = 0;
    }
    if (left) {
        // Do something
        should_rotate = 1 - should_rotate;
    }
    if (start_spin_) {
        // Spin object around an axis
        ball1.start_spin();
    }
    if (stop_spin_) {
        ball1.stop_spin();
    }
    if (cam1){
        // ball1.reset_position();
            target = ball1.get_position();
        camera_spot = 1;
    }
    if (cam2){
        // ball1.reset_position();
            target = ball1.get_position();
        camera_spot = 2;
    }
    if (cam3){
        // ball1.reset_position();
            target = ball1.get_position();
        camera_spot = 3;
    }
}

void tick_elements() {
    ball1.tick();
    // camera_rotation_angle += 1;
}


void chooseModel() {
    if (select_model == 0){
        ball1 = Ball(0, 0, COLOR_GREEN);
    } else if(select_model == 1) {
        ball1 = HexagonalDipyramid(0, 0, COLOR_GREEN);
    } else if(select_model == 2) {
        ball1 = DecagonalPrism(0, 0, COLOR_GREEN);
    } else if(select_model == 3) {
        ball1 = UndecagonalPyramid(0, 0, COLOR_GREEN);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    
    chooseModel();

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    
    if (argc >= 2) {
        // cerr << "Hello: " << argv[1] << "\n\n\n";
        select_model = stoi(argv[1]);
    } else {
        cout << "Models available:\n";
        cout << "1. Hexagonal Dipyramid.\n";
        cout << "2. Decagonal Prism.\n";
        cout << "3. Undecagonal Pyramid.\n";
        cout << "Please enter the model number you want to choose: ";
        cin >> select_model;
        if (select_model < 1 || select_model > 3) {
            select_model = 2;
            cout << "You have entered an incorrect model number, so going with Decagonal Prism.\n";
        }
    }
    
    int width  = 1800;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glfwSwapBuffers(window);
        // glfwPollEvents();
        // Boiler below
        
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


void make_maze() {
    vector<char> dir;
    dir.push_back('N');
    dir.push_back('S');
    dir.push_back('E');
    dir.push_back('W');
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    shuffle(dir.begin(), dir.end(), e);
    
}