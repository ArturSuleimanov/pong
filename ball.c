#include "ball.h"
#include <stdlib.h>
#include <time.h>

struct ball initBall(int x, int y) {
  struct ball ball;
  ball.view = '@';
  resetBall(&ball, x, y);
  return ball;
}

void resetBall(struct ball *ball, int x, int y) {
  ball->x = x;
  ball->y = y;
  srand(time(NULL));
  int rand1 = rand() % 2;
  int rand2 = rand() % 2;
  ball->vx = (rand1 == 0) ? rand1 - 1 : rand1;
  ball->vy = (rand2 == 0) ? rand2 - 1 : rand2;
}
