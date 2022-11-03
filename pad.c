#include "pad.h"
#include <stdlib.h>

struct pad initPad(int y) {
  struct pad pad;
  resetPad(&pad, y);
  return pad;
}

void resetPad(struct pad *pad, int y) { pad->y = y; }
