#include "map.h"

#include <gb/gb.h>
#include <gb/cgb.h>
#include <string.h>

#include "math.h"

uint8_t bank;
map_t map;
uint8_t map_x, map_y, last_map_x, last_map_y;
uint16_t buf_w, buf_h;
uint16_t scr_x, scr_y, target_scr_x, target_scr_y, last_scr_x, last_scr_y;

uint8_t map_buffer[MAP_BUFF_SIZE * MAP_BUFF_SIZE];

void map_load(map_t* map_data, uint8_t map_bank) NONBANKED
{
	map = *map_data;
	bank = map_bank;
	buf_w = map.width * MAP_MT_SIZE;
	buf_h = map.height * MAP_MT_SIZE;
	last_map_x = map_x = 0, last_map_y = map_y = 0;
	scr_x = target_scr_x = last_scr_x = 0, scr_y = target_scr_y = last_scr_y = 0;
	map_update_buffer(0, 0, map.width, map.height);
}

void map_buffer_mt(uint16_t subtile_x, uint16_t subtile_y, uint8_t metatile)
{
	uint8_t* map_buf_ptr = map_buffer + subtile_x + (subtile_y * MAP_BUFF_SIZE);
	metatile_t* mt = map.metatiles + metatile;
	*map_buf_ptr = mt->subtiles[0];
	map_buf_ptr++;
	*map_buf_ptr = mt->subtiles[1];
	map_buf_ptr += MAP_BUFF_SIZE - MAP_MT_SIZE;
	*map_buf_ptr = mt->subtiles[2];
	map_buf_ptr++;
	*map_buf_ptr = mt->subtiles[3];
}

void map_update_buffer(uint8_t x, uint8_t y, uint8_t width, uint8_t height) NONBANKED
{
	for(uint8_t mt_y = y; mt_y < y + height; mt_y++)
	{
		for(uint8_t mt_x = x; mt_x < x + width; mt_x++)
		{
			uint8_t mt_idx = map.tilemap[mt_x + (mt_y * map.width)];
			map_buffer_mt(mt_x * MAP_MT_SIZE, mt_y * MAP_MT_SIZE, mt_idx);
		}
	}
}

uint8_t map_get_metatile(uint8_t tile_x, uint8_t tile_y) NONBANKED
{
	uint8_t _prev_bank = _current_bank;
	SWITCH_ROM(bank);
	uint8_t tile = map.tilemap[tile_x + tile_y * map.width];
	SWITCH_ROM(_prev_bank);
	return tile;
}

void map_set_scroll(uint16_t x, uint16_t y) NONBANKED
{
	scr_x = target_scr_x = x;
	scr_y = target_scr_y = y;
}

void map_scroll_to(uint16_t x, uint16_t y) NONBANKED
{
	target_scr_x = x;
	target_scr_y = y;
}

void map_update(void) NONBANKED
{
	if(scr_x < target_scr_x)
		scr_x++;
	else if(scr_x > target_scr_x)
		scr_x--;
	if(scr_y < target_scr_y)
		scr_y++;
	else if(scr_y > target_scr_y)
		scr_y--;
	SCX_REG = scr_x, SCY_REG = scr_y;
	map_x = scr_x >> 3;
	map_y = scr_y >> 3;

	if(last_map_x != map_x)
	{
		if(scr_x < last_scr_x)
		{
			set_bkg_submap(map_x, map_y, MIN(21u, buf_w - map_x), 1, map_buffer, buf_w);
		}
		else // scr_x >= last_scr_x
		{
			if((buf_h - 18u) > map_y)
				set_bkg_submap(map_x, map_y + 18u, MIN(21u, buf_w - map_x), 1, map_buffer, buf_w);
		}
		last_map_x = map_x;
	}

	if(last_map_y != map_y)
	{
		if(scr_y < last_scr_y)
		{

		}
		else // scr_y >= last_scr_y
		{

		}
		last_map_y = map_y;
	}
	last_scr_x = scr_x, last_scr_y = scr_y;
}