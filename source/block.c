#include "block.h"



struct Block block_create_inactive(sf2d_texture *sprite) {

	struct Block b;
	b.sprite = sprite;
	b.x = 0;
	b.y = 0;
	b.z = 0;
	b.width = 0;
	b.height = 0;
	b.active = false;
	return b;
}

struct Block block_create(float x, float y, float z, unsigned int width, unsigned int height, sf2d_texture *sprite) {

	struct Block b;
	b.sprite = sprite;
	b.x = x;
	b.y = y;
	b.z = z;
	b.width = width;
	b.height = height;
	b.active = true;
	
	return b;
}


void block_draw(struct Block *b, float slider_state) {
	
	if (b->active) {
		float x3d = b->z * slider_state;
		/*if (slider_state > 0) { // Right eye
			x3d = -b->z;
		}
		else if (slider_state < 0) { // Left eye
			x3d = b->z;
		}*/
		// sf2d_draw_rectangle(b->x + x3d, b->y, b->width, b->height, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
		sf2d_draw_texture(b->sprite, b->x + x3d, b->y);
	}
}

void block_destroy(struct Block *b) {
	// sf2d_free_texture(b->sprite);
}