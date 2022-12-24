#pragma bank 1
#include "fade.h"

#include "math.h"

uint8_t fade_enable_bg = 0xFF, fade_enable_obj = 0xFF;
palette_color_t fade_bg_pal[GBC_PAL_COUNT * GBC_PAL_COLOR_COUNT];
palette_color_t fade_obj_pal[GBC_PAL_COUNT * GBC_PAL_COLOR_COUNT];

uint8_t fade_in_op(palette_color_t c, palette_color_t i)
{
	return U_LESS_THAN(c, i) ? 0 : (c - i);
}

palette_color_t update_color(uint8_t fade_step, palette_color_t col)
{
	uint16_t fade_mask = shift_right(0x1F, FADE_STEP_END - fade_step);
	return PAL_RGB8(
		PAL_RED(col)	& fade_mask,
		PAL_GREEN(col)	& fade_mask,
		PAL_BLUE(col)	& fade_mask
	);
}

void fade_step_color(uint8_t fade_step)
{
	uint8_t pal_idx, c;
	palette_color_t pal[GBC_PAL_COLOR_COUNT], pal_s[GBC_PAL_COLOR_COUNT];
	palette_color_t* col = fade_bg_pal;
	palette_color_t* col_s = fade_obj_pal;

	for(pal_idx = 0; pal_idx < GBC_PAL_COUNT; pal_idx++)
	{
		for(c = 0; c < GBC_PAL_COLOR_COUNT; ++c, ++col, ++col_s)
		{
			pal[c] = update_color(fade_step, *col);
			pal_s[c] = update_color(fade_step, *col_s);
		}
		if(GET_BIT(fade_enable_bg, pal_idx))
			set_bkg_palette(pal_idx, 1, pal);
		if(GET_BIT(fade_enable_obj, pal_idx))
			set_sprite_palette(pal_idx, 1, pal_s);
	}
}

void fade_in(uint8_t fade_delay)
{
	uint8_t fade_step, current_delay;
	for(fade_step = 0; fade_step != FADE_STEP_COUNT; fade_step++)
	{
		fade_step_color(fade_step);
		current_delay = fade_delay;
		while(current_delay)
		{
			wait_vbl_done();
			current_delay--;
		}
	}
	
}

void fade_out(uint8_t fade_delay)
{
	uint8_t fade_step, current_delay;
	for(fade_step = FADE_STEP_END; fade_step != 0xFF; --fade_step)
	{
		fade_step_color(fade_step);
		current_delay = fade_delay;
		while(current_delay)
		{
			wait_vbl_done();
			current_delay--;
		}
	}
}

void fade_set(uint8_t fade_step)
{
	if(fade_step > FADE_STEP_END)
		fade_step = FADE_STEP_END;
	fade_step_color(fade_step);
}

void fade_enable_pal(pal_type_e pal_type, uint8_t pal_idx, uint8_t enable_fade)
{
	if(pal_type == PAL_TYPE_BG)
		if(enable_fade)
			SET_BIT(fade_enable_bg, pal_idx);
		else
			UNSET_BIT(fade_enable_bg, pal_idx);
	else
		if(enable_fade)
			SET_BIT(fade_enable_obj, pal_idx);
		else
			UNSET_BIT(fade_enable_obj, pal_idx);
}

void fade_enable_pals(pal_type_e pal_type, uint8_t enable_fade)
{
	if(pal_type == PAL_TYPE_BG)
		if(enable_fade)
			fade_enable_bg = 0xFF;
		else
			fade_enable_bg = 0x00;
	else
		if(enable_fade)
			fade_enable_obj = 0xFF;
		else
			fade_enable_obj = 0x00;
}

void fade_enable_all(uint8_t enable_fade)
{
	if(enable_fade)
		fade_enable_bg = fade_enable_obj = 0xFF;
	else
		fade_enable_bg = fade_enable_obj = 0x00;
}