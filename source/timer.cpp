#include "timer.h"
#include <GLFW/glfw3.h>

Timer::Timer(double interval) {
    prev = 0;
    this->interval = interval;
}

bool Timer::processTick() {
    double cur = glfwGetTime();
    if (cur - prev >= interval) {
        prev = cur;
        return true;
    } else
        return false;
}

bool Timer::processMove() {
    double cur = glfwGetTime();
    if (cur - prev_move >= 0.2) {
        prev_move = cur;
        return true;
    } else
        return false;
}
