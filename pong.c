#include "ball.h"
#include "field.h"
#include "pad.h"
#include "player.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SCORE 21
#define SLEEP 2000000

void replay(struct pad *padLeft, struct pad *padRight, struct ball *ball);
void gameplay(void);
void getAction(struct pad *padLeft, struct pad *padRight, int *delay,
               int *flag);
void countBallSpeed(struct ball *ball, struct pad *padLeft,
                    struct pad *padRight);
void ifSomeoneScored(struct ball *ball, struct pad *padLeft,
                     struct pad *padRight, struct player *player1,
                     struct player *player2);
void printPong(void);
void whoWin(struct player *player1, struct player *player2);

int main(void) {
  char agreement = 'y';
  while (agreement == 'y') {
    gameplay();
    printf("Do you want to play again? (y/n)\n");
    agreement = getchar();
    getchar();
    while (agreement != 'y' && agreement != 'n') {
      printf("Do you want to play again? (y/n)");
      agreement = getchar();
      getchar();
    }
  }
  return 0;
}

void replay(struct pad *padLeft, struct pad *padRight, struct ball *ball) {
  resetBall(ball, W / 2, H / 2);
  resetPad(padLeft, H / 2);
  resetPad(padRight, H / 2);
}

void gameplay(void) {
  initscr();
  cbreak();
  nodelay(stdscr, TRUE);
  noecho();
  clear();
  printPong();
  refresh();
  usleep(SLEEP);
  struct ball ball = initBall(W / 2, H / 2);
  struct pad padLeft = initPad(H / 2);
  struct pad padRight = initPad(H / 2);
  struct field field = initField(&padLeft, &padRight, &ball);
  struct player player1 = initPlayer();
  struct player player2 = initPlayer();
  player1.points = 0;
  player2.points = 0;
  int flag = 1;
  int delay = 100000;
  while ((player1.points < MAX_SCORE && player2.points < MAX_SCORE) && flag) {
    clear();
    printField(&field, &padLeft, &padRight, &ball, &player1, &player2, delay);
    refresh();
    usleep(delay);
    getAction(&padLeft, &padRight, &delay, &flag);
    countBallSpeed(&ball, &padLeft, &padRight);
    ifSomeoneScored(&ball, &padLeft, &padRight, &player1, &player2);
  }
  clear();
  whoWin(&player1, &player2);
  refresh();
  usleep(SLEEP);
  endwin();
  destroyField(&field);
}

void getAction(struct pad *padLeft, struct pad *padRight, int *delay,
               int *flag) {
  char action = getch();
  if (action == 'a' && padLeft->y != 2) {
    padLeft->y -= 1;
  } else if (action == 'z' && padLeft->y != H - 3) {
    padLeft->y += 1;
  } else if (action == 'k' && padRight->y != 2) {
    padRight->y -= 1;
  } else if (action == 'm' && padRight->y != H - 3) {
    padRight->y += 1;
  } else if (action == 'q') {
    *flag = 0;
  } else if (action == '=') {
    *delay = (*delay > 10000) ? *delay - 10000 : *delay;
  } else if (action == '-') {
    *delay = (*delay < 200000) ? *delay + 5000 : *delay;
  }
}

void countBallSpeed(struct ball *ball, struct pad *padLeft,
                    struct pad *padRight) {
  if (ball->x == 2 && ball->y == padLeft->y - 1) {
    ball->vx = -ball->vx;
    ball->vy = -1;
  } else if (ball->x == 2 && ball->y == padLeft->y + 1) {
    ball->vx = -ball->vx;
    ball->vy = 1;
  } else if (ball->x == 2 && ball->y == padLeft->y) {
    ball->vx = -ball->vx;
    ball->vy = 0;
  } else if (ball->x == W - 3 && ball->y == padRight->y - 1) {
    ball->vx = -ball->vx;
    ball->vy = -1;
  } else if (ball->x == W - 3 && ball->y == padRight->y + 1) {
    ball->vx = -ball->vx;
    ball->vy = 1;
  } else if (ball->x == W - 3 && ball->y == padRight->y) {
    ball->vx = -ball->vx;
    ball->vy = 0;
  }
  ball->x += ball->vx;
  ball->y += ball->vy;
  if (ball->y == 1 || ball->y == H - 2) {
    ball->vy = -ball->vy;
  }
}

void ifSomeoneScored(struct ball *ball, struct pad *padLeft,
                     struct pad *padRight, struct player *player1,
                     struct player *player2) {
  if (ball->x == 1) {
    player2->points++;
    replay(padLeft, padRight, ball);
  } else if (ball->x == W - 2) {
    player1->points++;
    replay(padLeft, padRight, ball);
  }
}

void printPong(void) {
  printw("__________                      \n");
  printw("\\______   \\____   ____    ____  \n");
  printw(" |     ___/  _ \\ /    \\  / ___\\ \n");
  printw(" |    |  (  <_> )   |  \\/ /_/  >\n");
  printw(" |____|   \\____/|___|  /\\___  / \n");
  printw("                     \\//_____/  \n");
}

void whoWin(struct player *player1, struct player *player2) {
  if (player1->points == MAX_SCORE) {
    printw("__________.__                               ____          .__      "
           "  \n");
    printw("\\______   \\  | _____  ___.__. ___________  /_   | __  _  _|__| "
           "____  \n");
    printw(" |     ___/  |\\__  \\ <   |  |/ __ \\_  __ \\  |   | \\ \\/ \\/ / "
           " |/    \\ \n");
    printw(" |    |   |  |__/ __ \\\\___  \\  ___/|  | \\/  |   |  \\     /|  "
           "|   |  \\\n");
    printw(" |____|   |____(____  / ____|\\___  >__|     |___|   \\/\\_/ "
           "|__|___|  /\n");
    printw("                    \\/\\/         \\/                             "
           "  \\/ \n");
  } else if (player2->points == MAX_SCORE) {
    printw("__________.__                              ________           .__  "
           "      \n");
    printw("\\______   \\  | _____  ___.__. ___________  \\_____  \\  __  _  "
           "_|__| ____  \n");
    printw(" |     ___/  | \\__  \\ <   |  |/ __ \\_  __ \\  /  ____/  \\ \\/ "
           "\\/ /  |/    \\ \n");
    printw(" |    |   |  |__/ __ \\\\___  \\  ___/|  | \\/ /       \\   \\     "
           "/|  |   |  \\\n");
    printw(" |____|   |____(____  / ____|\\___  >__|    \\_______ \\   \\/\\_/ "
           "|__|___|  /\n");
    printw("                    \\/\\/         \\/                \\/          "
           "       \\/ \n");
  }
}
