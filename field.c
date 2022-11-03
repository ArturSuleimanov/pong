#include "field.h"
#include "ball.h"
#include "pad.h"
#include "player.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#define H 27
#define W 82

struct field initField(struct pad *padLeft, struct pad *padRight,
                        struct ball *ball) {
  struct field field;
  field.view = (char **)malloc(H * sizeof(char **));
  for (int i = 0; i < H; i++) {
    field.view[i] = (char *)malloc(W * sizeof(char *));
  }
  generateField(&field, padLeft, padRight, ball);
  return field;
}

void generateField(struct field *field, struct pad *padLeft,
                   struct pad *padRight, struct ball *ball) {
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (i == 0 || i == H - 1) {
        field->view[i][j] = '=';
      } else if (j == W / 2 - 1 || j == W / 2) {
        field->view[i][j] = '|';
      } else {
        field->view[i][j] = ' ';
      }
      fieldMotion(field, padLeft, padRight, ball, i, j);
    }
  }
}

void fieldMotion(struct field *field, struct pad *padLeft, struct pad *padRight,
                 struct ball *ball, int i, int j) {
  if (i >= padLeft->y - 1 && i <= padLeft->y + 1 && j == 1) {
    field->view[i][j] = '|';
  } else if (i >= padRight->y - 1 && i <= padRight->y + 1 && j == W - 2) {
    field->view[i][j] = '|';
  }
  field->view[ball->y][ball->x] = ball->view;
}

void printField(struct field *field, struct pad *padLeft, struct pad *padRight,
                struct ball *ball, struct player *player1,
                struct player *player2, int delay) {
  generateField(field, padLeft, padRight, ball);
  printw("Delay: %d\n", delay);
  printw("Player1: %d          Player2: %d\n", player1->points,
         player2->points);
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      printw("%c", field->view[i][j]);
    }
    printw("\n");
  }
}

void destroyField(struct field *field) {
  for (int i = 0; i < H; i++) {
    free(field->view[i]);
  }
  free(field->view);
}
