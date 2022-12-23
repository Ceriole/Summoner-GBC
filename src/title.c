// Bank pragma for autobanking
#pragma bank 255

#include "title.h"

#include "sys/music.h"

#include "res/screens/title.h"
#include "res/sprites/bluefire.h"
#include "res/sprites/buttons.h"
#include "res/sprites/buttons_anim.h"

#include "gfx/object.h"
#include "gfx/banked_gfx.h"

#include "sys/input.h"
#include "sys/fade.h"

#include "sys/palette.h"

DECLARE_MUSIC(mus_title);

BANKREF(title_init)
void title_init(void) BANKED
{
	SPRITES_8x16;

	load_palette(PAL_TYPE_BG, BKGF_CGB_PAL0, title_PALETTE_COUNT, title_palettes, BANK(title));
	load_palette(PAL_TYPE_OBJ, OAMF_CGB_PAL0, bluefire_PALETTE_COUNT, bluefire_palettes, BANK(bluefire));
	fade_set(0);

	set_banked_sprite_data(0u, bluefire_TILE_COUNT, bluefire_tiles, BANK(bluefire));

	set_banked_bkg_data(0u, title_TILE_COUNT, title_tiles, BANK(title));
	/* Select VRAM bank 1 */
	rVBK = VBK_ATTRIBUTES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, title_WIDTH / title_TILE_W, title_HEIGHT / title_TILE_H, title_map_attributes, BANK(title));

	/* Select VRAM bank 1 */
	rVBK = VBK_TILES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, title_WIDTH / title_TILE_W, title_HEIGHT / title_TILE_H, title_map, BANK(title));
}

BANKREF(title_sequence)
void title_sequence(void) BANKED
{
    title_init();
	music_play(&mus_title, BANK(mus_title));
    fade_in(10);
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