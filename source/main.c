#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <3ds.h>
#include <sf2d.h>

#include "block.h"
#include "player.h"

#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)
#define BLOCK_NUMBER 64


void player_check_collision(struct Player *p, struct Block (*blocks)[BLOCK_NUMBER]) {
	
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
		if (blocks[block_index]->x < p->bbox_right && blocks[block_index]->x + blocks[block_index]->width > p->bbox_left) { // Collision posible
		
			if (p->vspeed > 0) { // While falling
		
				// Landing on ground
				if (blocks[block_index]->y <= p->bbox_bottom && blocks[block_index]->y + blocks[block_index]->height > p->bbox_bottom) {
					p->vspeed  = 0;
					p->gravity = 0;
					player_set_sprite(p, ANIMATION_STAND);
					p->y += blocks[block_index]->y - p->bbox_bottom;
				}
			
			}
		}
	}
	
}


int main()
{
	// Set the random seed based on the time
	srand(time(NULL));

	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	sf2d_set_3D(1);

	struct Block blocks[BLOCK_NUMBER];
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
		blocks[block_index] = block_create_inactive();
	}

	blocks[0] = block_create(48, 192, 6, 16, 16);
	blocks[1] = block_create(64, 192, 6, 16, 16);

	struct Player p1 = player_create(32, 138, 8);
	

	u32 held;

	while (aptMainLoop()) {

		hidScanInput();
		// hidCircleRead(&circle);
		held = hidKeysHeld();

		if (held & KEY_START) {
			break;
		/*} else if (held & KEY_TOUCH) {
			hidTouchRead(&touch);
			touch_x = touch.px;
			touch_y = touch.py;*/
		} else if (held & (KEY_L | KEY_R)) {
			sf2d_set_clear_color(RGBA8(rand()%255, rand()%255, rand()%255, 255));
		}
		
		
		player_controll(&p1, held);

		player_refresh_sprite(&p1);
		
		// Player movement
		player_move(&p1);
		
		// Check if player lands on ground or crashes against blocks
		player_check_collision(&p1, &blocks);
		

		// offset3d = CONFIG_3D_SLIDERSTATE * 30.0f;

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
	}

	player_destroy(&p1);
	for (unsigned int block_index = 0; block_index < BLOCK_NUMBER; block_index++) {
		block_destroy(&blocks[block_index]);
	}

	sf2d_fini();
	return 0;
}
