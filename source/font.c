#include "font.h"

#include "img/font_sprites.c"

struct Font font_create() {

	struct Font f;

	f.num[0] = sf2d_create_texture_mem_RGBA8(font_lcd_9.pixel_data, font_lcd_9.width, font_lcd_9.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	
	return f;
	
}

void draw_text(struct Font *f) {
	
	sf2d_draw_texture(f->num[0], 20, 20);
	
}