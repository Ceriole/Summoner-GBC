#ifndef __BANKED_GFX_H__
#define __BANKED_GFX_H__

#include "banked_func.h"

BANKED_DATA_FUNC_EXTERN(set_banked_bkg_data, uint8_t first_tile, uint8_t nb_tiles, const uint8_t* data);
BANKED_DATA_FUNC_EXTERN(set_banked_sprite_data, uint8_t first_tile, uint8_t nb_tiles, const uint8_t* data);

BANKED_DATA_FUNC_EXTERN(set_banked_bkg_tiles, uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* tiles);
BANKED_DATA_FUNC_EXTERN(set_banked_bkg_based_tiles, uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* tiles, uint8_t base_tile);

BANKED_DATA_FUNC_EXTERN(set_banked_bkg_submap, uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* tiles, uint8_t map_w);
BANKED_DATA_FUNC_EXTERN(set_banked_bkg_based_submap, uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* tiles, uint8_t base_tile);

BANKED_DATA_FUNC_EXTERN(set_banked_bkg_palette, uint8_t first_palette, uint8_t nb_palettes, const palette_color_t* rgb_data);
BANKED_DATA_FUNC_EXTERN(set_banked_sprite_palette, uint8_t first_palette, uint8_t nb_palettes, const palette_color_t* rgb_data);

#endif