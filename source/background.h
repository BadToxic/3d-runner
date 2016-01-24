#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <sf2d.h>

struct Background {
  sf2d_texture *sprite;
  float x;
  float y;
  float z;
  unsigned int width;
  unsigned int height;
  float speed; // 1 is 100%
};

struct Background background_create(float, float, float, unsigned int, unsigned int, float, sf2d_texture *);

void background_draw(struct Background*, float);

void background_destroy(struct Background*);

#endif /* BACKGROUND_H */