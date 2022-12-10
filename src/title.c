#include "title.h"

#include "res/gen/title.h"
#include "res/gen/bluefire.h"

#include "gfx/object.h"
#include "gfx/banked_gfx.h"

// Bank pragma for autobanking
#pragma bank 255

BANKREF(title_init)
void title_init(void) BANKED
{
    set_banked_bkg_palette(BKGF_CGB_PAL0, title_PALETTE_COUNT, (palette_color_t*) title_palettes, BANK(title));
	set_banked_sprite_palette(OAMF_CGB_PAL0, bluefire_PALETTE_COUNT, (palette_color_t*) bluefire_palettes, BANK(bluefire));

	set_banked_sprite_data(0u, bluefire_TILE_COUNT, bluefire_tiles, BANK(bluefire));

	set_banked_bkg_data(0u, title_TILE_COUNT, title_tiles, BANK(title));
	/* Select VRAM bank 1 */
	VBK_REG = VBK_ATTRIBUTES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, title_WIDTH / title_TILE_W, title_HEIGHT / title_TILE_H, title_map_attributes, BANK(title));

	/* Select VRAM bank 1 */
	VBK_REG = VBK_TILES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, title_WIDTH / title_TILE_W, title_HEIGHT / title_TILE_H, title_map, BANK(title));

	SHOW_BKG;
	SHOW_SPRITES; SPRITES_8x16; 
	enable_interrupts();
	DISPLAY_ON;
}

BANKREF(title_sequence)
void title_sequence(void) BANKED
{
    title_init();
    
    title_loop();
}

BANKREF(title_loop)
void title_loop(void) BANKED
{
    while(1)
    {
        wait_vbl_done();
    }
}