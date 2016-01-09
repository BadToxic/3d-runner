#include "block.h"

struct Block block_create(float x, float y, float z, unsigned int width, unsigned int height) {

	struct Block b;
	b.x = x;
	b.y = y;
	b.z = z;
	b.width = width;
	b.height = height;
	b.active = true;
	
	return b;
}

struct Block block_create_inactive() {

	struct Block b;
	b.x = 0;
	b.y = 0;
	b.z = 0;
	b.width = 0;
	b.height = 0;
	b.active = false;
	
	return b;
}

void block_draw(struct Block *b, int eye) {
	
	if (b->active) {
		int x3d = 0;
		if (eye > 0) { // Right eye
			x3d = -b->z;
		}
		else if (eye < 0) { // Left eye
			x3d = b->z;
		}
		sf2d_draw_rectangle(b->x + x3d, b->y, b->width, b->height, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
	}
}

void block_destroy(struct Block *b) {
	
}