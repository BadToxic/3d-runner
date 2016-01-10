#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "img/player_sprites.c"


void player_set_sprite_stand(struct Player *p) {

	if (p->animation_id != ANIMATION_STAND) {
		p->animation_id = ANIMATION_STAND;
		memcpy(p->sprite_array, p->sprite_stand, sizeof p->sprite_stand);
		p->sprite       = p->sprite_array[0];
		p->image_number = p->sprite_stand_image_number;
		p->image_index  = 0;
		p->image_index_counter = 0;
		p->image_speed  = 0;
	}
	
}

void player_set_sprite_run(struct Player *p) {

	if (p->animation_id != ANIMATION_RUN) {
		p->animation_id = ANIMATION_RUN;
		memcpy(p->sprite_array, p->sprite_run, sizeof p->sprite_run);
		p->sprite       = p->sprite_array[0];
		p->image_number = p->sprite_run_image_number;
		p->image_index  = 0;
		p->image_index_counter = 0;
		p->image_speed  = 0.2;
	}
	
}

void player_set_sprite_jump(struct Player *p) {

	if (p->animation_id != ANIMATION_JUMP) {
		p->animation_id = ANIMATION_JUMP;
		memcpy(p->sprite_array, p->sprite_jump, sizeof p->sprite_jump);
		p->image_index  = round(rand() % 2);
		p->image_index_counter = p->image_index;
		p->sprite       = p->sprite_array[p->image_index];
		p->image_number = p->sprite_jump_image_number;
		p->image_speed  = 0;
	}
	
}

void player_set_sprite(struct Player *p, int animation_id) {

	if (p->animation_id != animation_id) {
		if (animation_id == ANIMATION_STAND) {
			player_set_sprite_stand(p);
		}
		else if (animation_id == ANIMATION_RUN) {
			player_set_sprite_run(p);
		}
		else if (animation_id == ANIMATION_JUMP) {
			player_set_sprite_jump(p);
		}
	}
	
}

void player_jump(struct Player *p) {
	if (p->animation_id != ANIMATION_JUMP) {
		player_set_sprite(p, ANIMATION_JUMP);
		p->vspeed  = -p->jump_power;
		p->gravity = GRAVITY;
		p->jump_button_released = false;
	}
}

void player_refresh_bbox(struct Player *p) {
	p->bbox_left   = p->x + 23;
	p->bbox_right  = p->x + 40;
	p->bbox_top    = p->y + 10;
	p->bbox_bottom = p->y + 52;
}

struct Player player_create() {

	struct Player p;
	p.x = 0;
	p.y = 0;
	p.z = 0;
	
	player_refresh_bbox(&p);	
	
	p.vspeed     = 0;
    p.gravity    = 0;
	p.jump_power = 12;
	p.jump_button_released = true;
	
	p.sprite_stand_image_number = 1;
	p.sprite_stand[0] = sf2d_create_texture_mem_RGBA8(spr_char_stand.pixel_data, spr_char_stand.width, spr_char_stand.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	p.sprite_run_image_number = 6;
	p.sprite_run[0] = sf2d_create_texture_mem_RGBA8(spr_char_run_1.pixel_data, spr_char_run_1.width, spr_char_run_1.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	p.sprite_run[1] = sf2d_create_texture_mem_RGBA8(spr_char_run_2.pixel_data, spr_char_run_2.width, spr_char_run_2.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	p.sprite_run[2] = sf2d_create_texture_mem_RGBA8(spr_char_run_3.pixel_data, spr_char_run_3.width, spr_char_run_3.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	p.sprite_run[3] = sf2d_create_texture_mem_RGBA8(spr_char_run_4.pixel_data, spr_char_run_4.width, spr_char_run_4.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	p.sprite_run[4] = sf2d_create_texture_mem_RGBA8(spr_char_run_5.pixel_data, spr_char_run_5.width, spr_char_run_5.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	p.sprite_run[5] = sf2d_create_texture_mem_RGBA8(spr_char_run_6.pixel_data, spr_char_run_6.width, spr_char_run_6.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	p.sprite_jump_image_number = 2;
	p.sprite_jump[0] = sf2d_create_texture_mem_RGBA8(spr_char_jump_1.pixel_data, spr_char_jump_1.width, spr_char_jump_1.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	p.sprite_jump[1] = sf2d_create_texture_mem_RGBA8(spr_char_jump_2.pixel_data, spr_char_jump_2.width, spr_char_jump_2.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	
	p.animation_id = -1;
	player_set_sprite(&p, ANIMATION_STAND);
	
	return p;
}

struct Player player_create_position(float x, float y, float z) {

	struct Player p = player_create();
	p.x = x;
	p.y = y;
	p.z = z;
	
	player_refresh_bbox(&p);	
	
	return p;
}


void player_refresh_sprite(struct Player *p) {

	if (p->image_number > 1 && p->image_speed > 0) {
		p->image_index_counter += p->image_speed;
		if (p->image_index_counter >= p->image_number) {
			p->image_index_counter = 0;
		}
		unsigned int next_index = floor(p->image_index_counter);
		if (p->image_index != next_index) {
			p->image_index = next_index;
			p->sprite = p->sprite_array[p->image_index];
		}
	}
	
}

void player_controll(struct Player *p, u32 held) {
	
	if (p->gravity == 0) {
		if (held & KEY_A && p->jump_button_released) {
			player_jump(p);
		}
		else {
			if (!(held & KEY_A)) {
				p->jump_button_released = true;
			}
			
			/*if (held & KEY_RIGHT) {
				player_set_sprite(p, ANIMATION_RUN);
			}
			else {
				player_set_sprite(p, ANIMATION_STAND);
			}*/
		}
	}
	else if (p->vspeed < 0) { // Still jumping upwards
		if (!(held & KEY_A)) {	// Slow down upwards movement
			p->vspeed /= 2;
		}
	}
	
}

void player_move(struct Player *p) {
	
	// Jumping or falling
	if (p->gravity != 0) {
		// I'm not on the ground yet
		
		p->y += p->vspeed;
		p->vspeed += p->gravity;
		
		player_refresh_bbox(p);
	}
	
}

void player_draw(struct Player *p, float slider_state) {
	
	float x3d = p->z * slider_state;
	/*if (slider_state > 0) { // Right eye
		x3d = -p->z;
	}
	else if (slider_state < 0) { // Left eye
		x3d = p->z;
	}*/
	sf2d_draw_texture(p->sprite, p->x + x3d, p->y);
	
}

void player_destroy(struct Player *p) {

	for (unsigned int image_index = 0; image_index < p->sprite_stand_image_number; image_index++) {
		sf2d_free_texture(p->sprite_stand[image_index]);
	}
	for (unsigned int image_index = 0; image_index < p->sprite_run_image_number; image_index++) {
		sf2d_free_texture(p->sprite_run[image_index]);
	}
	
}