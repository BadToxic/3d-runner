#ifndef FONT_H
#define FONT_H

#include <sf2d.h>

struct Font {

  sf2d_texture *num[10];
  sf2d_texture *dot;
  sf2d_texture *colon;
  unsigned int w;

};

struct Font font_create();

void draw_time(struct Font*, float, unsigned int, unsigned int);

void draw_float(struct Font*, float, unsigned int, unsigned int, unsigned int);

#endif /* FONT_H */