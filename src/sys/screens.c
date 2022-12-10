#include "screens.h"

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#include "gfx/banked_gfx.h"

#include "res/gen/gbc_required.h"

static const uint8_t scanline_offsets_tbl[] = {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0};
static const uint8_t * scanline_offsets = scanline_offsets_tbl;

// Bank pragma for autobanking
#pragma bank 255

BANKREF(screen_cgb_required_isr)
void screen_cgb_required_isr() BANKED {
    SCX_REG = scanline_offsets[LY_REG & (uint8_t)7];
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
        scanline_offsets = &scanline_offsets_tbl[(uint8_t)(sys_time >> 2) & 0x07u];
    }
}