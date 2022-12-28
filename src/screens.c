// Bank pragma for autobanking
#pragma bank 255

#include "screens.h"

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#include "gfx/banked_gfx.h"

#include "res/screens/gbc_required.h"
#include "res/screens/cerisoft.h"

#include "sys/music.h"
#include "sys/input.h"

#include "gfx/palette.h"
#include "gfx/fade.h"

DECLARE_MUSIC(mus_cerisoft);

BANKREF(screen_cgb_required)
void screen_cgb_required(void) BANKED
{
	HIDE_BKG;
	set_banked_bkg_data(gbc_required_TILE_ORIGIN, gbc_required_TILE_COUNT, gbc_required_tiles, BANK(gbc_required));
	set_banked_bkg_tiles(0, 0, gbc_required_WIDTH / gbc_required_TILE_W, gbc_required_HEIGHT / gbc_required_TILE_H, gbc_required_map, BANK(gbc_required));
	SHOW_BKG;

	while (1) {
		wait_vbl_done();
	}
}

#define CERISOFT_PREFADE_DELAY 1000
#define CERISOFT_FADE_DELAY 10
#define CERISOFT_EXIT_DELAY 80

BANKREF(screen_studio)
void screen_studio(void) BANKED
{
	set_banked_bkg_data(cerisoft_TILE_ORIGIN, cerisoft_TILE_COUNT, cerisoft_tiles, BANK(cerisoft));
	load_palette(PAL_TYPE_BG, 0, 1, cerisoft_palettes, BANK(cerisoft));
	fade_set(0);

	rVBK = VBK_ATTRIBUTES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, cerisoft_WIDTH / cerisoft_TILE_W, cerisoft_HEIGHT / cerisoft_TILE_H, cerisoft_map_attributes, BANK(cerisoft));
	/* Select VRAM bank 1 */
	rVBK = VBK_TILES;
	set_banked_bkg_tiles(0, 0, cerisoft_WIDTH / cerisoft_TILE_W, cerisoft_HEIGHT / cerisoft_TILE_H, cerisoft_map, BANK(cerisoft));
	
	delay(CERISOFT_PREFADE_DELAY);

	fade_in(CERISOFT_FADE_DELAY);

	MUSIC_PLAY(&mus_cerisoft, BANK(mus_cerisoft));

	for(uint8_t i = 0; i < CERISOFT_EXIT_DELAY; i++)
	{
		if(joys.joy0)
			break;
		wait_vbl_done();
	}

	fade_out(CERISOFT_FADE_DELAY);

	delay(CERISOFT_PREFADE_DELAY);
}