#ifndef PAD_H_
#define PAD_H_
#include "stdlib.h"

struct pad {
  int y;
};

struct pad initPad(int y);
void resetPad(struct pad *pad, int y);

#endif  // PAD_H_
