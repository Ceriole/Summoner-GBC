#include "title.h"

#include "sys/music.h"

#include "res/screens/title.h"
#include "res/sprites/bluefire.h"
#include "res/sprites/buttons.h"
#include "res/sprites/buttons_anim.h"

#include "gfx/object.h"
#include "gfx/banked_gfx.h"

#include "sys/input.h"

// Bank pragma for autobanking
#pragma bank 255

BANKREF_EXTERN(mus_title)
extern const hUGESong_t mus_title;

object_t button_prompt_a, button_prompt_b, button_prompt_pad;

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
 
	set_interrupts(VBL_IFLAG | TIM_IFLAG);
	music_play(&mus_title, BANK(mus_title));

	aabb_t button_bb;
	create_object(&button_prompt_a, OBJ_SCRN_TO_POS(SCREENWIDTH - 16 - 8), OBJ_SCRN_TO_POS(SCREENHEIGHT - 16 - 8), button_bb, bluefire_TILE_COUNT, buttons_anim, buttons_metasprites);
	create_object(&button_prompt_b, OBJ_SCRN_TO_POS(SCREENWIDTH - 16 - 16 - 9), OBJ_SCRN_TO_POS(SCREENHEIGHT - 16 - 8), button_bb, bluefire_TILE_COUNT, buttons_anim, buttons_metasprites);
	create_object(&button_prompt_pad, OBJ_SCRN_TO_POS(16 + 16 + 8), OBJ_SCRN_TO_POS(SCREENHEIGHT - 16 - 8), button_bb, bluefire_TILE_COUNT, buttons_anim, buttons_metasprites);
	obj_set_anim(&button_prompt_a, BUTTONS_ANIM_A_INDEX);
	obj_set_anim(&button_prompt_b, BUTTONS_ANIM_B_INDEX);
	obj_set_anim(&button_prompt_pad, BUTTONS_ANIM_DPAD_INDEX);

	SHOW_BKG;
	SHOW_SPRITES; SPRITES_8x16; 
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
		input_update();

		if(joys.joy0 & J_A)
			obj_set_anim(&button_prompt_a, BUTTONS_ANIM_A_MASH_INDEX);
		else
			obj_set_anim(&button_prompt_a, BUTTONS_ANIM_A_INDEX);
		if(joys.joy0 & J_B)
			obj_set_anim(&button_prompt_b, BUTTONS_ANIM_B_MASH_INDEX);
		else
			obj_set_anim(&button_prompt_b, BUTTONS_ANIM_B_INDEX);
		if(joys.joy0 & J_UP)
			obj_set_anim(&button_prompt_pad, BUTTONS_ANIM_UP_PRESS_INDEX);
		else if(joys.joy0 & J_DOWN)
			obj_set_anim(&button_prompt_pad, BUTTONS_ANIM_DOWN_PRESS_INDEX);
		else
			obj_set_anim(&button_prompt_pad, BUTTONS_ANIM_DPAD_INDEX);

		obj_update(&button_prompt_a);
		obj_update(&button_prompt_b);
		obj_update(&button_prompt_pad);

		uint8_t oam_idx = 0;
		oam_idx = obj_render(&button_prompt_a, oam_idx);
		oam_idx = obj_render(&button_prompt_b, oam_idx);
		oam_idx = obj_render(&button_prompt_pad, oam_idx);
		hide_sprites_range(oam_idx, 40);

		wait_vbl_done();
	}
}