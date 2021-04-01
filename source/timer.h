#ifndef TIMER_H
#define TIMER_H


class Timer {
public:
    Timer() {
        prev = 0;
        prev_move = 0;
        prev_enemy = 0;
    }
    Timer(double interval);
    double interval;
    bool processTick();
    bool processMove();
    bool moveEnemy();
    bool processSecond();
private:
    double prev;
    double prev_move;
    double prev_enemy;
    double prev_second;
};

#endif // TIMER_H
