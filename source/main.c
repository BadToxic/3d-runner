#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <3ds.h>
#include <sf2d.h>

#include "util.h"

#include "img/background_sprites.c"
#include "background.h"
#include "img/spr_controlls.c"
#include "font.h"
#include "block.h"
#include "img/spr_block.c"
#include "player.h"

#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)
#define ROOM_SPEED 60
#define BACKGROUND_NUMBER 3
#define FOREGROUND_NUMBER 1
#define BLOCK_NUMBER 64
#define ROOM_WIDTH 412
#define ROOM_HEIGHT 240

bool show_debug = false; // Turn this of when not needed
float debug_float = 0;
char debug_string[128];

sf2d_texture *controlls;
sf2d_texture *block_sprite;
const float new_block_counter_max    = 16;  // Pixels to run by before a new block will be created
float new_block_counter              = 0;   // Pixels to run by before a new block will be created
const unsigned int new_block_y_start = 192; // y coordinate the blocks will start to be generated
float new_block_y           	     = 0;
unsigned int blocks_following_min    = 0;
unsigned int blocks_following_max    = 0;
unsigned int blocks_following        = 0;
unsigned int empty_following_min     = 0;
unsigned int empty_following_max     = 0;
unsigned int empty_following         = 0;
bool next_is_block = true;

const float countdown 	  = 0; //0.2; // Time in seconds till the game starts
const float run_speed_max = 4;
const float run_speed_inc = 0.01;
const int player_x_start  = 32;
const int player_y_start  = 140;
const int player_z_start  = 8;


float time_played = 0; // Passed time in seconds
float run_speed   = 4; // 0;

bool game_over = false;

void start_new_game (struct Player *p, struct Block blocks[]) {
	
	game_over = false;
	new_block_counter = 0;
	new_block_y       = new_block_y_start;
	blocks_following_min    = 20;
	blocks_following_max    = 20;
		
	time_played = 0;
	run_speed   = 0;
	
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
		blocks[block_index] = block_create_inactive(block_sprite);
	}

	// Create start ground
	for (unsigned int block_index = 0; block_index < 28; block_index++) {
		blocks[block_index] = block_create(-16 + block_index * 16, new_block_y, 6, 16, 16, block_sprite);
	}
	
	p->x = player_x_start;
	p->y = player_y_start;
	p->z = player_z_start;
	player_set_sprite(p, ANIMATION_STAND);
	p->vspeed     = 0;
	p->gravity    = 0;
	p->jump_power = 12;
	p->jump_button_released = true;
	player_refresh_bbox(p);
	
}


void generate_new_blocks(struct Block blocks[]) {

	// Decide if new block has to be generated
	
	if (next_is_block) {
		if (blocks_following >= blocks_following_max) {
			next_is_block = false;
		}
		else if (blocks_following >= blocks_following_min) {
			if (round(rand() % 2) == 0) {
				next_is_block = false;
			}
		}
		if (!next_is_block) { // Changed
			blocks_following    = 0;
			empty_following_min = 2;
			empty_following_max = 6;
		}
	}
	else if (!next_is_block) {
		if (empty_following >= empty_following_max) {
			next_is_block = true;
		}
		else if (empty_following >= empty_following_min) {
			if (round(rand() % 2) == 0) {
				next_is_block = true;
			}
		}
		if (next_is_block) { // Changed
			empty_following      = 0;
			blocks_following_min = 6;
			blocks_following_max = 16;
		}
	}
	
	if (next_is_block) {
		int first_active_block_index = -1;
		// Search first active block position in array
		for (unsigned int block_index = 1; block_index < BLOCK_NUMBER; block_index++) {
			if (blocks[block_index].active) {
				first_active_block_index = block_index;
				break;
			}	
		}
		
		// Search first empty position in array
		for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
			if (!blocks[block_index].active) {
				blocks[block_index] = block_create(416, new_block_y, 6, 16, 16, block_sprite);
				// blocks[block_index].x -= ((int) blocks[block_index].x) % 16;
				if (first_active_block_index >= 0) {
					debug_float = 16.0 - ((float)(((int)((blocks[first_active_block_index].x + 32) * 100.0)) % 1600)) / 100.0;
					blocks[block_index].x -= 16.0 - ((float)(((int)((blocks[first_active_block_index].x + 32) * 100.0)) % 1600)) / 100.0;   ///////////////////////////////////////////
				}
				else {
					debug_float += 100;
				}
				break;
			}	
		}
		
		blocks_following++;
	}
	else {
	
	
		empty_following++;
	}
}

void player_check_collision(struct Player *p, struct Block blocks[]) {
	
	if (p->vspeed > 0) { // While falling
	
		for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
			if (blocks[block_index].active) {
				if (blocks[block_index].x < p->bbox_right && blocks[block_index].x + blocks[block_index].width > p->bbox_left) { // Collision posible
			
					// Landing on ground
					if (blocks[block_index].y <= p->bbox_bottom && blocks[block_index].y + blocks[block_index].height > p->bbox_bottom) {
						p->vspeed  = 0;
						p->gravity = 0;
						if (run_speed == 0) {
							player_set_sprite(p, ANIMATION_STAND);
						}
						else {
							player_set_sprite(p, ANIMATION_RUN);
						}
						p->y += blocks[block_index].y - p->bbox_bottom;
						player_refresh_bbox(p);
					}
				
				}
			}
		}
		
	}
	else if (p->vspeed == 0) { // While walking
		bool on_ground = false;
		for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
			if (blocks[block_index].active) {
				if (blocks[block_index].x < p->bbox_right && blocks[block_index].x + blocks[block_index].width > p->bbox_left) { // Collision posible
			
					// Loosing ground
					if (blocks[block_index].y <= p->bbox_bottom && blocks[block_index].y + blocks[block_index].height > p->bbox_bottom) {
						on_ground = true;
						break;
					}
				
				}
			}
		}
		if (!on_ground) {
			player_fall(p);
		}
	}
	
}


int main() {

	// Set the random seed based on the time
	srand(time(NULL));

	//gfxInitDefault();
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	sf2d_set_3D(1);

	
	// Backgrounds
	struct Background backgrounds[BACKGROUND_NUMBER];
	if (BACKGROUND_NUMBER > 0) {
		backgrounds[0] = background_create(0, 128, 0, 512, 128, 0.8, sf2d_create_texture_mem_RGBA8(spr_background_1.pixel_data, spr_background_1.width, spr_background_1.height, TEXFMT_RGBA8, SF2D_PLACE_RAM));
		if (BACKGROUND_NUMBER > 1) {
			backgrounds[1] = background_create(0, 0, -12, 512, 240, 0.4, sf2d_create_texture_mem_RGBA8(spr_background_2.pixel_data, spr_background_2.width, spr_background_2.height, TEXFMT_RGBA8, SF2D_PLACE_RAM));
			if (BACKGROUND_NUMBER > 2) {
				backgrounds[2] = background_create(0, 0, 0, 412, 128, 0, sf2d_create_texture_mem_RGBA8(spr_background_static.pixel_data, spr_background_static.width, spr_background_static.height, TEXFMT_RGBA8, SF2D_PLACE_RAM));
			}
		}
	}
	// Foregrounds
	struct Background foregrounds[FOREGROUND_NUMBER];
	if (FOREGROUND_NUMBER > 0) {
		foregrounds[0] = background_create(0, 208, 16, 512, 32, 1.2, sf2d_create_texture_mem_RGBA8(spr_foreground_1.pixel_data, spr_foreground_1.width, spr_foreground_1.height, TEXFMT_RGBA8, SF2D_PLACE_RAM));
	}

	struct Font fnt = font_create();

	controlls = sf2d_create_texture_mem_RGBA8(spr_controlls.pixel_data, spr_controlls.width, spr_controlls.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	block_sprite = sf2d_create_texture_mem_RGBA8(spr_block.pixel_data, spr_block.width, spr_block.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	struct Block blocks[BLOCK_NUMBER];
	

	struct Player p1 = player_create();
	start_new_game(&p1, blocks);

	u32 held;

	while (aptMainLoop()) {

		time_t unixTime = time(NULL);
		struct tm* current_time = gmtime((const time_t *)&unixTime);
		
		// Main controll
		hidScanInput();
		held = hidKeysHeld();

		if (held & KEY_START) {
			break;
		} else if (held & KEY_SELECT) { // Set player back to start position (for testing)
		
			start_new_game(&p1, blocks);
			
			// Show current time: test
			getTimeString(debug_string, current_time);
			
		}
		
		
		if (!game_over) {
			time_played += 1 / (float)ROOM_SPEED;

			if (time_played > countdown) { // Start running after this time in seconds
				if (run_speed < run_speed_max) {
					if (run_speed < 1) {
						if (run_speed == 0) { // Start run animation
							if (p1.animation_id == ANIMATION_STAND) {
								player_set_sprite(&p1, ANIMATION_RUN);
							}
						}
						run_speed += run_speed_inc * 4;
					}
					else {
						run_speed += run_speed_inc;
					}
				}
			}
			// ftoa(time_played, debug_string, 2);
		
		}
		else {
			if (run_speed > 0) {
				run_speed -= run_speed_inc;
				if (run_speed < 0) {
					run_speed = 0;
				}
			}
		}
		
		// Move backgrounds
		for (unsigned int background_index = 0; background_index < BACKGROUND_NUMBER; background_index++) {
			if (backgrounds[background_index].speed != 0) {
				backgrounds[background_index].x -= run_speed * backgrounds[background_index].speed;
			}
		}
		
		// Move foregrounds
		for (unsigned int foreground_index = 0; foreground_index < FOREGROUND_NUMBER; foreground_index++) {
			if (foregrounds[foreground_index].speed != 0) {
				foregrounds[foreground_index].x -= run_speed * foregrounds[foreground_index].speed;
			}
		}
		
		// Move blocks
		for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
			if (blocks[block_index].active) {
				blocks[block_index].x -= run_speed;
				if (blocks[block_index].x < -((float) blocks[block_index].width) - 16) {
					blocks[block_index].active = false;
				}
			}
		}
		
		// Create new blocks
		if (new_block_counter > new_block_counter_max) {
			generate_new_blocks(blocks);
			new_block_counter -= new_block_counter_max;
		}
		new_block_counter += run_speed;
		// ftoa(run_speed, debug_string, 2);
		
		if (!game_over) {
			// Player controlling
			player_controll(&p1, held);

			player_refresh_sprite(&p1);
			if (p1.animation_id == ANIMATION_RUN) {
				p1.image_speed = run_speed / 16;
			}
			
			// Player movement
			player_move(&p1);
			
			// Check if player lands on ground or crashes against blocks
			player_check_collision(&p1, blocks);
			
			if (p1.y > ROOM_HEIGHT) {
				game_over = true;
			}
		}

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
			// Backgrounds
			for (int background_index = BACKGROUND_NUMBER - 1; background_index >= 0; background_index--) {
				background_draw(&backgrounds[background_index], CONFIG_3D_SLIDERSTATE);
			}
		
		
			for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
				block_draw(&blocks[block_index], CONFIG_3D_SLIDERSTATE);
			}
			player_draw(&p1, CONFIG_3D_SLIDERSTATE);
			
			// Foregrounds
			for (unsigned int foreground_index = 0; foreground_index < FOREGROUND_NUMBER; foreground_index++) {
				background_draw(&foregrounds[foreground_index], CONFIG_3D_SLIDERSTATE);
			}
			
		sf2d_end_frame();


		sf2d_start_frame(GFX_TOP, GFX_RIGHT);

			// Backgrounds
			for (int background_index = BACKGROUND_NUMBER - 1; background_index >= 0; background_index--) {
				background_draw(&backgrounds[background_index], -CONFIG_3D_SLIDERSTATE);
			}

			for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
				block_draw(&blocks[block_index], -CONFIG_3D_SLIDERSTATE);
			}
			player_draw(&p1, -CONFIG_3D_SLIDERSTATE);
			
			// Foregrounds
			for (unsigned int foreground_index = 0; foreground_index < FOREGROUND_NUMBER; foreground_index++) {
				background_draw(&foregrounds[foreground_index], -CONFIG_3D_SLIDERSTATE);
			}
			
		sf2d_end_frame();

		
		// Bottom Screen
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		
			
			sf2d_draw_texture(controlls, 0, 0);
			
			draw_time(&fnt, time_played, 20, 20);
			
			if (show_debug) {
				draw_float(&fnt, debug_float, 2, 300, 20);
			}
			
			
		sf2d_end_frame();



		sf2d_swapbuffers();
		
		/*if (show_debug) {
			consoleInit(GFX_BOTTOM, NULL);
			printf("\x1b[15;2HDebug text: %s", debug_string);
		}*/
	}

	player_destroy(&p1);
	sf2d_free_texture(block_sprite);
	/*for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
		block_destroy(&blocks[block_index]);
	}*/
	sf2d_free_texture(controlls);
	for (int background_index = BACKGROUND_NUMBER - 1; background_index >= 0; background_index--) {
		background_destroy(&backgrounds[background_index]);
	}
	for (unsigned int foreground_index = 0; foreground_index < FOREGROUND_NUMBER; foreground_index++) {
		background_destroy(&foregrounds[foreground_index]);
	}

	sf2d_fini();
	return 0;
}

/*strcat(debug_string, "(");
char x_string[8];
ftoa(blocks[block_index].x, x_string, 1);
strcat(debug_string, x_string);*/