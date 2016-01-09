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
#define BLOCK_NUMBER 64

char debug_string[128];

void player_check_collision(struct Player *p, struct Block blocks[]) {
	
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
	
		if (blocks[block_index].active) {
		
			if (blocks[block_index].x < p->bbox_right && blocks[block_index].x + blocks[block_index].width > p->bbox_left) { // Collision posible
			
				if (p->vspeed > 0) { // While falling
					
					// Landing on ground
					if (blocks[block_index].y <= p->bbox_bottom && blocks[block_index].y + blocks[block_index].height > p->bbox_bottom) {
						p->vspeed  = 0;
						p->gravity = 0;
						player_set_sprite(p, ANIMATION_STAND);
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
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
		blocks[block_index] = block_create_inactive();
	}

	// Create start ground
	for (unsigned int block_index = 0; block_index < 26; block_index++) {
		blocks[block_index] = block_create(-16 + block_index * 16, 192, 6, 16, 16);
	}


	struct Player p1 = player_create(32, 138, 8);
	

	u32 held;

	while (aptMainLoop()) {

		hidScanInput();
		held = hidKeysHeld();

		if (held & KEY_START) {
			break;
		} else if (held & KEY_B) { // Set player back to start position (for testing)
			p1.x = 32;
			p1.y = 138;
			player_set_sprite(&p1, ANIMATION_STAND);
			p1.vspeed     = 0;
			p1.gravity    = 0;
			p1.jump_power = 12;
			p1.jump_button_released = true;
			player_refresh_bbox(&p1);
			
		} else if (held & (KEY_L | KEY_R)) {
			sf2d_set_clear_color(RGBA8(rand()%255, rand()%255, rand()%255, 255));
		}
		
		
		player_controll(&p1, held);

		player_refresh_sprite(&p1);
		
		// Player movement
		player_move(&p1);
		
		// Check if player lands on ground or crashes against blocks
		player_check_collision(&p1, blocks);
		

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
			for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
				block_draw(&blocks[block_index], -1);
			}
			player_draw(&p1, -1);
			
		sf2d_end_frame();


		sf2d_start_frame(GFX_TOP, GFX_RIGHT);

			for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
				block_draw(&blocks[block_index], 1);
			}
			player_draw(&p1, 1);
			
		sf2d_end_frame();




		sf2d_swapbuffers();
		
		
		
		consoleInit(GFX_BOTTOM, NULL);

		//Move the cursor to row 15 and column 19 and then prints "Hello World!"
		//To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
		//the row and column where you want your cursor to move
		//The top screen has 30 rows and 50 columns
		//The bottom screen has 30 rows and 40 columns
		printf("\x1b[15;2HDebug text: %s", debug_string);
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