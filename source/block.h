#ifndef BLOCK_H
#define BLOCK_H

#include <sf2d.h>

struct Block {
  float x;
  float y;
  float z;
  unsigned int width;
  unsigned int height;
  bool active;
  //sf2d_texture *sprite;
  //sf2d_texture *sprite_array[8];
  //unsigned int image_number;
  ///unsigned int image_index;
  //float image_index_counter;
  //float image_speed;
};

struct Block block_create(float, float, float, unsigned int, unsigned int);
struct Block block_create_inactive();

// void block_refresh_sprite(struct Block*);
void block_draw(struct Block*, int);

void block_destroy(struct Block*);

#endif /* BLOCK_H */