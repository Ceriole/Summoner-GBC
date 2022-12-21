#include "palette.h"

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <string.h>

extern palette_color_t fade_bg_pal[GBC_PAL_COUNT * GBC_PAL_COLOR_COUNT];
extern palette_color_t fade_obj_pal[GBC_PAL_COUNT * GBC_PAL_COLOR_COUNT];

void load_palette(pal_type_e pal_type, uint8_t first_palette, uint8_t nb_palettes, palette_color_t* rgb_data, uint8_t bank)
{
	if(first_palette + nb_palettes > 8)
		return; //Adding more palettes than supported

	uint16_t* pal_ptr = (pal_type == PAL_TYPE_BG) ? fade_bg_pal : fade_obj_pal;
    uint8_t __save = _current_bank;
    SWITCH_ROM(bank);
	if(pal_type == PAL_TYPE_BG) {
		set_bkg_palette(first_palette, nb_palettes, rgb_data);
	} else {
		set_sprite_palette(first_palette, nb_palettes, rgb_data);
	}
	memcpy(&pal_ptr[first_palette << 2], rgb_data, nb_palettes << 3);
    SWITCH_ROM(__save);
}