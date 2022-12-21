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

#include "sys/palette.h"
#include "sys/fade.h"

static const uint8_t cgb_req_scanline_offsets_tbl[] = {0, 1, 1, 1, 2, 2, 2, 1, 1, 1, 0, 0, 0, 1, 1, 1};
static const uint8_t * cgb_req_scanline_offsets = cgb_req_scanline_offsets_tbl;

DECLARE_MUSIC(mus_cerisoft);

BANKREF(screen_cgb_required_isr)
void screen_cgb_required_isr() BANKED {
	SCX_REG = cgb_req_scanline_offsets[LY_REG & (uint8_t)7];
}

BANKREF(screen_cgb_required)
void screen_cgb_required(void) BANKED
{
	set_banked_bkg_data(gbc_required_TILE_ORIGIN, gbc_required_TILE_COUNT, gbc_required_tiles, BANK(gbc_required));
	set_banked_bkg_tiles(0, 0, gbc_required_WIDTH / gbc_required_TILE_W, gbc_required_HEIGHT / gbc_required_TILE_H, gbc_required_map, BANK(gbc_required));
	SHOW_BKG; DISPLAY_ON;

	CRITICAL {
		STAT_REG = STATF_MODE01 | STATF_MODE00;
		add_LCD(screen_cgb_required_isr);
	}
	set_interrupts(VBL_IFLAG | TIM_IFLAG | LCD_IFLAG);

	while (1) {
		wait_vbl_done();        
		cgb_req_scanline_offsets = &cgb_req_scanline_offsets[(uint8_t)(sys_time >> 2) & 0x07u];
	}
}
/**
#define CERISOFT_FADEIN_LENGTH 3
static const palette_color_t cerisoft_fadein_palettes[4 * CERISOFT_FADEIN_LENGTH] = {
	RGB8(0, 0, 0), RGB8(0, 0, 0), RGB8(0, 0, 0), RGB8(0, 0, 0),
	RGB8(251 / 4u, 242 / 4u, 54 / 4u), RGB8(223 / 4u, 113 / 4u, 38 / 4u), RGB8(172 / 4u, 50 / 4u, 50 / 4u), RGB8(  0,  0,  0),
	RGB8(251 / 2u, 242 / 2u, 54 / 2u), RGB8(223 / 2u, 113 / 2u, 38 / 4u), RGB8(172 / 2u, 50 / 2u, 50 / 2u), RGB8(  0,  0,  0)
};
*/

#define CERISOFT_PREFADE_DELAY 80
#define CERISOFT_FADE_DELAY 10
#define CERISOFT_EXIT_DELAY 80
static uint8_t cerisoft_state, cerisoft_timer, cerisoft_fade_idx;

BANKREF(screen_studio)
void screen_studio(void) BANKED
{
	set_banked_bkg_data(cerisoft_TILE_ORIGIN, cerisoft_TILE_COUNT, cerisoft_tiles, BANK(cerisoft));
	load_palette(PAL_TYPE_BG, 0, 1, cerisoft_palettes, BANK(cerisoft));

	rVBK = VBK_ATTRIBUTES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, cerisoft_WIDTH / cerisoft_TILE_W, cerisoft_HEIGHT / cerisoft_TILE_H, cerisoft_map_attributes, BANK(cerisoft));
	/* Select VRAM bank 1 */
	rVBK = VBK_TILES;
	set_banked_bkg_tiles(0, 0, cerisoft_WIDTH / cerisoft_TILE_W, cerisoft_HEIGHT / cerisoft_TILE_H, cerisoft_map, BANK(cerisoft));

	rAUDENA = AUDENA_ON;
	rAUDTERM = 0xFF;
	rAUDVOL = AUDVOL_VOL_LEFT(0x7) | AUDVOL_VIN_LEFT | AUDVOL_VOL_RIGHT(0x7) | AUDVOL_VIN_RIGHT;
	
	SHOW_BKG; DISPLAY_ON;

	delay(CERISOFT_PREFADE_DELAY);
	
	music_play(&mus_cerisoft, BANK(mus_cerisoft));

	fade_out(CERISOFT_FADE_DELAY);

	for(uint8_t i = 0; i < CERISOFT_EXIT_DELAY; i++)
	{
		if(joys.joy0)
			break;
		wait_vbl_done();
	}

	fade_in(CERISOFT_FADE_DELAY);
}