#ifndef BLOCK_H
#define BLOCK_H

#include <sf2d.h>

struct Block {
  sf2d_texture *sprite;
  float x;
  float y;
  float z;
  unsigned int width;
  unsigned int height;
  bool active;
};

struct Block block_create_inactive(sf2d_texture *);
struct Block block_create(float, float, float, unsigned int, unsigned int, sf2d_texture *);

void block_draw(struct Block*, float);

void block_destroy(struct Block*);

#endif /* BLOCK_H */