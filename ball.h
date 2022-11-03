#ifndef BALL_H_
#define BALL_H_
#include <stdlib.h>
#include <time.h>

struct ball {
    char view;
    int x;
    int y;
    int vx;
    int vy;
};

struct ball initBall(int x, int y);
void resetBall(struct ball* ball, int x, int y);
#endif  // BALL_H_


