#include "block.h"

struct Block block_create(unsigned int x, unsigned int y, int z, unsigned int width, unsigned int height) {

	struct Block b;
	b.x = x;
	b.y = y;
	b.z = z;
	b.width = width;
	b.height = height;
	
	return b;
}

void block_draw(struct Block *b, int eye) {
	
	int x3d = 0;
	if (eye > 0) { // Right eye
		x3d = -b->z;
	}
	else if (eye < 0) { // Left eye
		x3d = b->z;
	}
	sf2d_draw_rectangle(b->x + x3d, b->y, b->width, b->height, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
}

void block_destroy(struct Block *b) {
	
}