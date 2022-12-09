#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#include "res/gen/title.h"
#include "res/gen/bluefire.h"

#include "gfx/object.h"

const uint8_t fire_animations[] = {
	7, 10, 0, 1, 2, 3, 4, 5, 6, 7
};

const uint8_t SIN_TABLE[] = {
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	96,
	99,
	102,
	104,
	106,
	109,
	111,
	113,
	115,
	117,
	118,
	120,
	121,
	123,
	124,
	125,
	126,
	126,
	127,
	127,
	127,
	128,
	127,
	127,
	127,
	126,
	126,
	125,
	124,
	123,
	121,
	120,
	118,
	117,
	115,
	113,
	111,
	109,
	106,
	104,
	102,
	99,
	96,
	94,
	91,
	88,
	85,
	82,
	79,
	76,
	73,
	70,
	67,
	64,
	61,
	58,
	55,
	52,
	49,
	46,
	43,
	40,
	37,
	34,
	32,
	29,
	26,
	24,
	22,
	19,
	17,
	15,
	13,
	11,
	10,
	8,
	7,
	5,
	4,
	3,
	2,
	2,
	1,
	1,
	1,
	0,
	1,
	1,
	1,
	2,
	2,
	3,
	4,
	5,
	7,
	8,
	10,
	11,
	13,
	15,
	17,
	19,
	22,
	24,
	26,
	29,
	32,
	34,
	37,
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61
};

object_t fire;

void main(void)
{
	set_bkg_palette(BKGF_CGB_PAL0, title_PALETTE_COUNT, (palette_color_t*) title_palettes);
	set_sprite_palette(OAMF_CGB_PAL0, bluefire_PALETTE_COUNT, (palette_color_t*) bluefire_palettes);

	set_sprite_data(0u, bluefire_TILE_COUNT, bluefire_tiles);

	set_bkg_data(0u, title_TILE_COUNT, title_tiles);
	/* Select VRAM bank 1 */
	VBK_REG = VBK_ATTRIBUTES;
	/* Set attributes */
	set_bkg_tiles(0, 0, title_WIDTH / title_TILE_W, title_HEIGHT / title_TILE_H, title_map_attributes);

	/* Select VRAM bank 1 */
	VBK_REG = VBK_TILES;
	/* Set attributes */
	set_bkg_tiles(0, 0, title_WIDTH / title_TILE_W, title_HEIGHT / title_TILE_H, title_map);

	create_object(&fire, OBJ_SCRN_TO_POS(SCREENWIDTH / 2), OBJ_SCRN_TO_POS(SCREENHEIGHT / 2), 0u, (animation_t*) fire_animations, bluefire_metasprites);

	SHOW_BKG; 
	SHOW_SPRITES; SPRITES_8x16; 
	enable_interrupts();
	DISPLAY_ON;

	while(1)
	{
		obj_update(&fire);
		fire.x += 8;
		fire.y = OBJ_SCRN_TO_POS(SCREENHEIGHT / 2) + 32 - (SIN_TABLE[fire.x % 128] >> 1);
		uint8_t dexxy = 0;
		dexxy = obj_render(&fire, dexxy);
		hide_sprites_range(dexxy, MAX_HARDWARE_SPRITES);

		wait_vbl_done();
	}
}