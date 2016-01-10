#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <3ds.h>
#include <sf2d.h>

#include "util.h"
#include "block.h"
#include "player.h"

#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)
#define ROOM_SPEED 60
#define BLOCK_NUMBER 64

bool show_debug = true; // Turn this of when not needed
char debug_string[128];

const float countdown 	  = 0.2; // Time in seconds till the game starts
const float run_speed_max = 4;
const float run_speed_inc = 0.01;
const int player_x_start  = 32;
const int player_y_start  = 138;
const int player_z_start  = 8;


float time_played = 0; // Passed time in seconds
float run_speed   = 0;

void start_new_game (struct Player *p, struct Block blocks[]) {
	
	time_played = 0;
	run_speed   = 0;
	
	
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
		blocks[block_index] = block_create_inactive();
	}

	// Create start ground
	for (unsigned int block_index = 0; block_index < 27; block_index++) {
		blocks[block_index] = block_create(-16 + block_index * 16, 192, 6, 16, 16);
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

void player_check_collision(struct Player *p, struct Block blocks[]) {
	
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
	
		if (blocks[block_index].active) {
		
			if (blocks[block_index].x < p->bbox_right && blocks[block_index].x + blocks[block_index].width > p->bbox_left) { // Collision posible
			
				if (p->vspeed > 0) { // While falling
					
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
					}
				
				}
			}
		}
	}
	
}


int main()
{
	// Set the random seed based on the time
	srand(time(NULL));

	

	//gfxInitDefault();
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	sf2d_set_3D(1);

	struct Block blocks[BLOCK_NUMBER];


	struct Player p1 = player_create();
	start_new_game(&p1, blocks);

	u32 held;

	while (aptMainLoop()) {

		time_t unixTime = time(NULL);
		struct tm* current_time = gmtime((const time_t *)&unixTime);
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
		
		hidScanInput();
		held = hidKeysHeld();

		if (held & KEY_START) {
			break;
		} else if (held & KEY_B) { // Set player back to start position (for testing)
		
			start_new_game(&p1, blocks);
			
			// Show current time: test
			getTimeString(debug_string, current_time);
			
			
		} /*else if (held & (KEY_L | KEY_R)) {
			sf2d_set_clear_color(RGBA8(rand() % 255, rand() % 255, rand() % 255, 255));
		}*/
		
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
		

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
			for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
				block_draw(&blocks[block_index], CONFIG_3D_SLIDERSTATE);
			}
			player_draw(&p1, CONFIG_3D_SLIDERSTATE);
			
		sf2d_end_frame();


		sf2d_start_frame(GFX_TOP, GFX_RIGHT);

			for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
				block_draw(&blocks[block_index], -CONFIG_3D_SLIDERSTATE);
			}
			player_draw(&p1, -CONFIG_3D_SLIDERSTATE);
			
		sf2d_end_frame();



		sf2d_swapbuffers();
		
		if (show_debug) {
			consoleInit(GFX_BOTTOM, NULL);
			printf("\x1b[15;2HDebug text: %s", debug_string);
		}
	}

	player_destroy(&p1);
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
		block_destroy(&blocks[block_index]);
	}

	sf2d_fini();
	return 0;
}

/*strcat(debug_string, "(");
char x_string[8];
ftoa(blocks[block_index].x, x_string, 1);
strcat(debug_string, x_string);*/