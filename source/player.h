#ifndef PLAYER_H
#define PLAYER_H

#include <sf2d.h>

#define ANIMATION_STAND    0
#define ANIMATION_RUN      1
#define ANIMATION_JUMP     2
#define ANIMATION_JUMPKICK 3
#define ANIMATION_SLIDE    4

#define GRAVITY 0.8

#define SLIDE_TIME_MAX 1

struct Player {
  float x;
  float y;
  float z;
  int bbox_left;
  int bbox_right;
  int bbox_top;
  int bbox_bottom;
  
  float vspeed;
  float jump_power;
  float gravity;
  bool jump_button_released;
  bool slide_button_released;
  float slide_counter;
  
  int animation_id;
  sf2d_texture *sprite;
  sf2d_texture *sprite_array[8];
  unsigned int sprite_stand_image_number;
  sf2d_texture *sprite_stand[8];
  unsigned int sprite_run_image_number;
  sf2d_texture *sprite_run[8];
  unsigned int sprite_jump_image_number;
  sf2d_texture *sprite_jump[8];
  unsigned int sprite_jumpkick_image_number;
  sf2d_texture *sprite_jumpkick[8];
  unsigned int sprite_slide_image_number;
  sf2d_texture *sprite_slide[8];
  unsigned int image_number;
  unsigned int image_index;
  float image_index_counter;
  float image_speed;
};

void player_set_sprite_stand(struct Player*);
void player_set_sprite_run(struct Player*);
void player_set_sprite_jump(struct Player*);

void player_set_sprite(struct Player*, int);

void player_jump(struct Player*);

void player_refresh_bbox(struct Player*);

struct Player player_create();
struct Player player_create_position(float, float, float);


void player_refresh_sprite(struct Player*);

void player_controll(struct Player*, u32);

void player_move(struct Player*);

void player_draw(struct Player*, float);

void player_destroy(struct Player*);

#endif /* PLAYER_H */