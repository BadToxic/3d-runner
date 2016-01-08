#ifndef PLAYER_H
#define PLAYER_H

#include <sf2d.h>

static const int ANIMATION_STAND = 0;
static const int ANIMATION_RUN   = 1;
static const int ANIMATION_JUMP  = 2;

struct Player {
  int x;
  int y;
  int z;
  unsigned int width;
  unsigned int height;
  int animation_id;
  sf2d_texture *sprite;
  sf2d_texture *sprite_array[8];
  unsigned int sprite_stand_image_number;
  sf2d_texture *sprite_stand[8];
  unsigned int sprite_run_image_number;
  sf2d_texture *sprite_run[8];
  unsigned int sprite_jump_image_number;
  sf2d_texture *sprite_jump[8];
  unsigned int image_number;
  unsigned int image_index;
  float image_index_counter;
  float image_speed;
};

void player_set_sprite_stand(struct Player*);
void player_set_sprite_run(struct Player*);
void player_set_sprite_jump(struct Player*);

void player_set_sprite(struct Player*, int);

struct Player player_create(int, int, int);


void player_refresh_sprite(struct Player*);

void player_draw(struct Player*, int);

void player_destroy(struct Player*);

#endif /* PLAYER_H */