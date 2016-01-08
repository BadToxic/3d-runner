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


int main()
{
	// Set the random seed based on the time
	srand(time(NULL));

	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	sf2d_set_3D(1);

	unsigned int block_number_max = 64;
	struct Block blocks[block_number_max];
	for (unsigned int block_index = 0; block_index < block_number_max; block_index++) {
		blocks[block_index] = block_create_inactive();
	}

	blocks[0] = block_create(48, 192, 6, 16, 16);
	blocks[1] = block_create(64, 192, 6, 16, 16);

	struct Player p1 = player_create(32, 138, 8);


	//float offset3d = 0.0f;
	//float rad = 0.0f;
	/*u16 touch_x = 320/2;
	u16 touch_y = 240/2;
	touchPosition touch;*/
	//circlePosition circle;
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
		
		if (held & KEY_A) {
			player_set_sprite(&p1, ANIMATION_JUMP);
		}
		else if (held & KEY_RIGHT) {
			player_set_sprite(&p1, ANIMATION_RUN);
		}
		else {
			player_set_sprite(&p1, ANIMATION_STAND);
		}


		player_refresh_sprite(&p1);

		// offset3d = CONFIG_3D_SLIDERSTATE * 30.0f;

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
			/*sf2d_draw_fill_circle(offset3d + 60, 100, 35, RGBA8(0x00, 0xFF, 0x00, 0xFF));
			sf2d_draw_fill_circle(offset3d + 180, 120, 55, RGBA8(0xFF, 0xFF, 0x00, 0xFF));

			sf2d_draw_rectangle_rotate(offset3d + 260, 20, 40, 40, RGBA8(0xFF, 0xFF, 0x00, 0xFF), -2.0f*rad);
			sf2d_draw_rectangle(offset3d + 20, 60, 40, 40, RGBA8(0xFF, 0x00, 0x00, 0xFF));
			sf2d_draw_rectangle(offset3d + 5, 5, 30, 30, RGBA8(0x00, 0xFF, 0xFF, 0xFF));*/
			
			for (unsigned int block_index = 0; block_index < block_number_max; block_index++) {
				block_draw(&blocks[block_index], -1);
			}
			player_draw(&p1, -1);
			
		sf2d_end_frame();


		sf2d_start_frame(GFX_TOP, GFX_RIGHT);

			/*sf2d_draw_fill_circle(60, 100, 35, RGBA8(0x00, 0xFF, 0x00, 0xFF));
			sf2d_draw_fill_circle(180, 120, 55, RGBA8(0xFF, 0xFF, 0x00, 0xFF));

			sf2d_draw_rectangle_rotate(260, 20, 40, 40, RGBA8(0xFF, 0xFF, 0x00, 0xFF), -2.0f*rad);
			sf2d_draw_rectangle(20, 60, 40, 40, RGBA8(0xFF, 0x00, 0x00, 0xFF));
			sf2d_draw_rectangle(5, 5, 30, 30, RGBA8(0x00, 0xFF, 0xFF, 0xFF));*/
			
			for (unsigned int block_index = 0; block_index < block_number_max; block_index++) {
				block_draw(&blocks[block_index], 1);
			}
			player_draw(&p1, 1);
			
		sf2d_end_frame();


		/*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_rectangle_rotate(190, 160, 70, 60, RGBA8(0xFF, 0xFF, 0xFF, 0xFF), 3.0f*rad);
			sf2d_draw_rectangle(30, 100, 40, 60, RGBA8(0xFF, 0x00, 0xFF, 0xFF));
			//sf2d_draw_texture_rotate(tex2, touch_x, touch_y, -rad);
			sf2d_draw_rectangle(160-15 + cosf(rad)*50.0f, 120-15 + sinf(rad)*50.0f, 30, 30, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
			sf2d_draw_fill_circle(40, 40, 35, RGBA8(0x00, 0xFF, 0x00, 0xFF));
		sf2d_end_frame();*/

		// rad += 0.2f;

		sf2d_swapbuffers();
	}

	player_destroy(&p1);
	for (unsigned int block_index = 0; block_index < block_number_max; block_index++) {
		block_destroy(&blocks[block_index]);
	}

	sf2d_fini();
	return 0;
}
