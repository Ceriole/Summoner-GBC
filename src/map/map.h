#ifndef __MAP_H__
#define __MAP_H__

#include <gbdk/platform.h>
#include <stdint.h>

#define MAP_MAX_SIZE 256
#define MAP_MT_SIZE 2
#define MAP_BUFF_SIZE 64

typedef struct
{
    uint8_t subtiles[MAP_MT_SIZE * MAP_MT_SIZE];
    uint8_t palette;
} metatile_t;

typedef struct
{
    uint8_t width, height;
    uint8_t tile_count;
    uint8_t* tile_data;
    uint8_t palette_count;
    palette_color_t* palette_data;
    uint8_t metatile_count;
    metatile_t* metatiles;
    uint8_t* tilemap;
} map_t;

void map_load(map_t* map_data, uint8_t map_bank) NONBANKED;
void map_update_buffer(uint8_t x, uint8_t y, uint8_t width, uint8_t height) NONBANKED;
uint8_t map_get_metatile(uint8_t tile_x, uint8_t tile_y) NONBANKED;
void map_set_scroll(uint16_t x, uint16_t y) NONBANKED;
void map_scroll_to(uint16_t x, uint16_t y) NONBANKED;
void map_update(void) NONBANKED;

#endif // __MAP_H__