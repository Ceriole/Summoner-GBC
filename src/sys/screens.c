#include "screens.h"

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#include "gfx/banked_gfx.h"

#include "res/screens/gbc_required.h"
#include "res/screens/cerisoft.h"

#include "sys/hUGE_banked.h"

static const uint8_t cgb_req_scanline_offsets_tbl[] = {0, 1, 1, 1, 2, 2, 2, 1, 1, 1, 0, 0, 0, 1, 1, 1};
static const uint8_t * cgb_req_scanline_offsets = cgb_req_scanline_offsets_tbl;

BANKREF_EXTERN(mus_cerisoft)
extern const hUGESong_t mus_cerisoft;

// Bank pragma for autobanking
#pragma bank 255

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
    set_interrupts(VBL_IFLAG | LCD_IFLAG);

    while (1) {
        wait_vbl_done();        
        cgb_req_scanline_offsets = &cgb_req_scanline_offsets[(uint8_t)(sys_time >> 2) & 0x07u];
    }
}

#define CERISOFT_FADEIN_LENGTH 3
static const palette_color_t cerisoft_fadein_palettes[4 * CERISOFT_FADEIN_LENGTH] = {
	RGB8(0, 0, 0), RGB8(0, 0, 0), RGB8(0, 0, 0), RGB8(0, 0, 0),
    RGB8(251 / 4u, 242 / 4u, 54 / 4u), RGB8(223 / 4u, 113 / 4u, 38 / 4u), RGB8(172 / 4u, 50 / 4u, 50 / 4u), RGB8(  0,  0,  0),
    RGB8(251 / 2u, 242 / 2u, 54 / 2u), RGB8(223 / 2u, 113 / 2u, 38 / 4u), RGB8(172 / 2u, 50 / 2u, 50 / 2u), RGB8(  0,  0,  0)
};

#define CERISOFT_STATE_PREFADE 0
#define CERISOFT_STATE_FADE_IN 1
#define CERISOFT_STATE_WAIT 2
#define CERISOFT_STATE_END 3

#define CERISOFT_PREFADE_DELAY 80
#define CERISOFT_FADEIN_DELAY 10
static uint8_t cerisoft_state, cerisoft_timer, cerisoft_fadein_idx;

BANKREF(screen_studio)
void screen_studio(void) BANKED
{
    set_banked_bkg_data(cerisoft_TILE_ORIGIN, cerisoft_TILE_COUNT, cerisoft_tiles, BANK(cerisoft));
    set_bkg_palette(0, 1, cerisoft_fadein_palettes);
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
    set_interrupts(VBL_IFLAG);
	enable_interrupts();
	
    cerisoft_timer = CERISOFT_PREFADE_DELAY;
    cerisoft_state = CERISOFT_STATE_PREFADE;

    while (cerisoft_state != CERISOFT_STATE_END) {
        switch(cerisoft_state)
        {
        case CERISOFT_STATE_PREFADE:
            if(cerisoft_timer)
                cerisoft_timer--;
            else
            {
                cerisoft_timer = CERISOFT_FADEIN_DELAY;
                cerisoft_fadein_idx = 0;
                cerisoft_state = CERISOFT_STATE_FADE_IN;
                hUGE_banked_init(&mus_cerisoft, BANK(mus_cerisoft));
            }
            break;
        case CERISOFT_STATE_FADE_IN:
            if(cerisoft_timer)
                cerisoft_timer--;
            else
            {
                cerisoft_timer = CERISOFT_FADEIN_DELAY;
                cerisoft_fadein_idx++;
                if(cerisoft_fadein_idx >= CERISOFT_FADEIN_LENGTH)
                {
                    set_banked_bkg_palette(0, 1, cerisoft_palettes, BANK(cerisoft));
                    cerisoft_state = CERISOFT_STATE_WAIT;
                }
                else
                    set_bkg_palette(0, 1, &cerisoft_fadein_palettes[cerisoft_fadein_idx * 4u]);
            }
            break;
        default:
        case CERISOFT_STATE_WAIT:
            break;
        }

        hUGE_banked_dosound();
        wait_vbl_done();
    }
}