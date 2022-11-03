#ifndef FIELD_H_
#define FIELD_H_
#include "ball.h"
#include "field.h"
#include "pad.h"
#include "player.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#define H 27
#define W 82

struct field {
  char **view;
};

struct field initField(struct pad *padLeft, struct pad *padRight,
                        struct ball *ball);
void fieldMotion(struct field *field, struct pad *padLeft, struct pad *padRight,
                 struct ball *ball, int i, int j);
void generateField(struct field *field, struct pad *padLeft,
                   struct pad *padRight, struct ball *ball);
void printField(struct field *field, struct pad *padLeft, struct pad *padRight,
                struct ball *ball, struct player *player1,
                struct player *player2, int delay);
void destroyField(struct field *field);

#endif  // FIELD_H_
