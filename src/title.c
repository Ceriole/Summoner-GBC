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

const animation_t button_anim_a_press = {6, {{0, 12}, {1, 5}, {2, 3}, {3, 3}, {4, 3}, {5, 6}}};
const animation_t button_anim_a_mash = {3, {{6, 3}, {7, 3}, {8, 5}}};
const animation_t button_anim_b_press = {6, {{9, 12}, {10, 5}, {11, 3}, {12, 3}, {13, 3}, {14, 6}}};
const animation_t button_anim_b_mash = {3, {{15, 3}, {16, 3}, {17, 5}}};
const animation_t* const button_prompt_anims[4] = {
	&button_anim_a_press, &button_anim_a_mash,
	&button_anim_b_press, &button_anim_b_mash
};

joypads_t joys, last_joys;
object_t button_prompt_a, button_prompt_b;

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
	create_object(&button_prompt_a, OBJ_SCRN_TO_POS(SCREENWIDTH - 16 - 8), OBJ_SCRN_TO_POS(SCREENHEIGHT - 16 - 8), button_bb, bluefire_TILE_COUNT, button_prompt_anims, buttons_metasprites);
	create_object(&button_prompt_b, OBJ_SCRN_TO_POS(SCREENWIDTH - 8), OBJ_SCRN_TO_POS(SCREENHEIGHT - 16 - 8), button_bb, bluefire_TILE_COUNT, button_prompt_anims, buttons_metasprites);
	obj_set_anim(&button_prompt_a, 0);
	obj_set_anim(&button_prompt_b, 2);

	SHOW_BKG;
	SHOW_SPRITES; SPRITES_8x16; 
	enable_interrupts();
	DISPLAY_ON;

	joypad_init(1, &joys);
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
		joypad_ex(&joys);
		if(joys.joy0 != last_joys.joy0)
		{
			if(joys.joy0 & J_A)
				obj_set_anim(&button_prompt_a, 1);
			else
				obj_set_anim(&button_prompt_a, 0);
			if(joys.joy0 & J_B)
				obj_set_anim(&button_prompt_b, 3);
			else
				obj_set_anim(&button_prompt_b, 2);
		}

		obj_update(&button_prompt_a);
		obj_update(&button_prompt_b);

		uint8_t oam_idx = 0;
		oam_idx = obj_render(&button_prompt_a, oam_idx);
		oam_idx = obj_render(&button_prompt_b, oam_idx);
		hide_sprites_range(oam_idx, 40);

		last_joys = joys;
        wait_vbl_done();
	}
}