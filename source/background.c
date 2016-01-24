#include "background.h"


struct Background background_create(float x, float y, float z, unsigned int width, unsigned int height, float speed, sf2d_texture *sprite) {

	struct Background b;
	b.sprite = sprite;
	b.x = x;
	b.y = y;
	b.z = z;
	b.width = width;
	b.height = height;
	b.speed = speed;
	
	return b;
}


void background_draw(struct Background *b, float slider_state) {
	
	float x3d = b->z * slider_state;
	if (b->x <= -1 * (float)b->width) {
		b->x += b->width;
	}
	
	// float xx = ((int)(b->x + x3d) % b->width) - b->width; 
	float xx = b->x + x3d;
	sf2d_draw_texture(b->sprite, xx, b->y);
	
	sf2d_draw_texture(b->sprite, xx + b->width, b->y);
	
}

void background_destroy(struct Background *b) {
	sf2d_free_texture(b->sprite);
}