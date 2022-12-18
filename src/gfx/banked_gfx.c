#include "sys/banked_func.h"

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

BANKED_DATA_FUNC(
    set_banked_bkg_data,
    set_bkg_data(first_tile, nb_tiles, data),
    uint8_t first_tile, uint8_t nb_tiles, const uint8_t* data)
BANKED_DATA_FUNC(
    set_banked_sprite_data,
    set_sprite_data(first_tile, nb_tiles, data),
    uint8_t first_tile, uint8_t nb_tiles, const uint8_t* data)
BANKED_DATA_FUNC(
    set_banked_bkg_tiles,
    set_bkg_tiles(x, y, w, h, tiles),
    uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* tiles)
BANKED_DATA_FUNC(
    set_banked_bkg_based_tiles,
    set_bkg_based_tiles(x, y, w, h, tiles, base_tile),
    uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* tiles, uint8_t base_tile)
BANKED_DATA_FUNC(
    set_banked_bkg_submap,
    set_bkg_submap(x, y, w, h, tiles, map_w),
    uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* tiles, uint8_t map_w)
BANKED_DATA_FUNC(
    set_banked_bkg_based_submap,
    set_bkg_based_submap(x, y, w, h, tiles, base_tile, map_w),
    uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* tiles, uint8_t base_tile, uint8_t map_w)
BANKED_DATA_FUNC(
    set_banked_bkg_palette,
    set_bkg_palette(first_palette, nb_palettes, rgb_data),
    uint8_t first_palette, uint8_t nb_palettes, palette_color_t* rgb_data)
BANKED_DATA_FUNC(
    set_banked_sprite_palette,
    set_sprite_palette(first_palette, nb_palettes, rgb_data),
    uint8_t first_palette, uint8_t nb_palettes, palette_color_t* rgb_data)