#include "title.h"

#include "hUGEDriver.h"

#include "res/title.h"
#include "res/bluefire.h"
#include "res/buttons.h"

#include "gfx/object.h"
#include "gfx/banked_gfx.h"

extern const hUGESong_t music_blue_ocean;

// Bank pragma for autobanking
#pragma bank 255

const animation_t buttom_anim_a_press = {6, 10, {0, 1, 2, 3, 4, 5}};
const animation_t buttom_anim_a_mash = {3, 8, {6, 7, 8}};
const animation_t* const button_prompt_anims[2] = {
	&buttom_anim_a_press, &buttom_anim_a_mash
};

object_t button_prompt;

BANKREF(title_init)
void title_init(void) BANKED
{
    set_banked_bkg_palette(BKGF_CGB_PAL0, title_PALETTE_COUNT, (palette_color_t*) title_palettes, BANK(title));
	set_banked_sprite_palette(OAMF_CGB_PAL0, bluefire_PALETTE_COUNT, (palette_color_t*) bluefire_palettes, BANK(bluefire));
	set_banked_sprite_palette(OAMF_CGB_PAL0 + bluefire_PALETTE_COUNT, buttons_PALETTE_COUNT, (palette_color_t*) buttons_palettes, BANK(buttons));

	set_banked_sprite_data(0u, bluefire_TILE_COUNT, bluefire_tiles, BANK(bluefire));
	set_banked_sprite_data(bluefire_TILE_COUNT, buttons_TILE_COUNT, buttons_tiles, BANK(buttons));

	set_banked_bkg_data(0u, title_TILE_COUNT, title_tiles, BANK(title));
	/* Select VRAM bank 1 */
	rVBK = VBK_ATTRIBUTES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, title_WIDTH / title_TILE_W, title_HEIGHT / title_TILE_H, title_map_attributes, BANK(title));

	/* Select VRAM bank 1 */
	rVBK = VBK_TILES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, title_WIDTH / title_TILE_W, title_HEIGHT / title_TILE_H, title_map, BANK(title));

	rAUDENA = AUDENA_ON;
	rAUDTERM = 0xFF;
	rAUDVOL = AUDVOL_VOL_LEFT(0x7) | AUDVOL_VIN_LEFT | AUDVOL_VOL_RIGHT(0x7) | AUDVOL_VIN_RIGHT;
	// In your initializtion code
	CRITICAL {
		hUGE_init(&music_blue_ocean);
	}

	aabb_t button_bb;
	create_object(&button_prompt, OBJ_SCRN_TO_POS(SCREENWIDTH - 16 - 8), OBJ_SCRN_TO_POS(SCREENHEIGHT - 16 - 8), button_bb, bluefire_TILE_COUNT, button_prompt_anims, buttons_metasprites);
	obj_set_anim(&button_prompt, 0);

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
		obj_update(&button_prompt);
		uint8_t oam_idx = 0;
		oam_idx = obj_render(&button_prompt, oam_idx);
		hide_sprites_range(oam_idx, 40);
        wait_vbl_done();
    }
}