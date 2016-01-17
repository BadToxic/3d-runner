#ifndef FONT_H
#define FONT_H

#include <sf2d.h>

struct Font {

  sf2d_texture *num[10];

};

struct Font font_create();

void draw_text(struct Font*);

#endif /* FONT_H */