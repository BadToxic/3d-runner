#include "block.h"

struct Block block_create(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {

	struct Block b;
	b.x = x;
	b.y = y;
	b.width = width;
	b.height = height;
	
	return b;
}

void block_destroy(struct Block *b) {
	
}