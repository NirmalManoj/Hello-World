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

bool Timer::moveEnemy() {
    double cur = glfwGetTime();
    if (cur - prev_enemy >= 1.0) {
        prev_enemy = cur;
        return true;
    } else
        return false;
}

bool Timer::processSecond() {
    double cur = glfwGetTime();
    if (cur - prev_second >= 1.0) {
        prev_second = cur;
        return true;
    } else
        return false;
}

