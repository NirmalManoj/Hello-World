#ifndef TIMER_H
#define TIMER_H


class Timer {
public:
    Timer() {
        prev = 0;
        prev_move = 0;
    }
    Timer(double interval);
    double interval;
    bool processTick();
    bool processMove();
private:
    double prev;
    double prev_move;
};

#endif // TIMER_H
