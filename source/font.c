#include "font.h"

#include "img/font_sprites.c"

struct Font font_create() {

	struct Font f;

	f.num[0] = sf2d_create_texture_mem_RGBA8(font_lcd_0.pixel_data, font_lcd_0.width, font_lcd_0.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[1] = sf2d_create_texture_mem_RGBA8(font_lcd_1.pixel_data, font_lcd_1.width, font_lcd_1.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[2] = sf2d_create_texture_mem_RGBA8(font_lcd_2.pixel_data, font_lcd_2.width, font_lcd_2.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[3] = sf2d_create_texture_mem_RGBA8(font_lcd_3.pixel_data, font_lcd_3.width, font_lcd_3.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[4] = sf2d_create_texture_mem_RGBA8(font_lcd_4.pixel_data, font_lcd_4.width, font_lcd_4.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[5] = sf2d_create_texture_mem_RGBA8(font_lcd_5.pixel_data, font_lcd_5.width, font_lcd_5.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[6] = sf2d_create_texture_mem_RGBA8(font_lcd_6.pixel_data, font_lcd_6.width, font_lcd_6.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[7] = sf2d_create_texture_mem_RGBA8(font_lcd_7.pixel_data, font_lcd_7.width, font_lcd_7.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[8] = sf2d_create_texture_mem_RGBA8(font_lcd_8.pixel_data, font_lcd_8.width, font_lcd_8.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.num[9] = sf2d_create_texture_mem_RGBA8(font_lcd_9.pixel_data, font_lcd_9.width, font_lcd_9.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	
	f.dot    = sf2d_create_texture_mem_RGBA8(font_lcd_dot.pixel_data, font_lcd_dot.width, font_lcd_dot.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.colon  = sf2d_create_texture_mem_RGBA8(font_lcd_colon.pixel_data, font_lcd_colon.width, font_lcd_colon.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	f.w = 10;
	
	return f;
	
}

void draw_time(struct Font *f, float seconds, unsigned int x, unsigned int y) {

	unsigned int c = (int)(seconds * (float)100) % 100;
	unsigned int s = (int)seconds % 60;
	unsigned int m = (int)((seconds - ((int)seconds % 60)) / 60) % 60;
	unsigned int h = (seconds - ((int)seconds % 3600)) / 3600;	
	
	sf2d_draw_texture(f->num[h / 10], x, y); x += f->w;
	sf2d_draw_texture(f->num[h % 10], x, y); x += f->w;
	
	sf2d_draw_texture(f->colon, x, y); x += f->w;
	
	sf2d_draw_texture(f->num[m / 10], x, y); x += f->w;
	sf2d_draw_texture(f->num[m % 10], x, y); x += f->w;
	
	sf2d_draw_texture(f->colon, x, y); x += f->w;
	
	sf2d_draw_texture(f->num[s / 10], x, y); x += f->w;
	sf2d_draw_texture(f->num[s % 10], x, y); x += f->w;
	
	sf2d_draw_texture(f->dot, x, y); x += f->w;
	
	sf2d_draw_texture(f->num[c / 10], x, y); x += f->w;
	sf2d_draw_texture(f->num[c % 10], x, y); x += f->w;
	
}