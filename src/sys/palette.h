#ifndef __PALETTE_H__
#define __PALETTE_H__

#include <stdint.h>
#include <gb/cgb.h>

#define GBC_PAL_COUNT 8
#define GBC_PAL_COLOR_COUNT 4

#define PAL_RGB8(R, G, B) (((uint16_t) (R)) | ((uint16_t)(G) << 5) | (((uint16_t) (B)) << 8) << 2)

#define PAL_RED(C)		(((C) >> 0	) & 0x1F)
#define PAL_GREEN(C)	(((C) >> 5	) & 0x1F)
#define PAL_BLUE(C)		(((C) >> 10	) & 0x1F)

typedef enum {
	PAL_TYPE_BG,
	PAL_TYPE_OBJ
} pal_type_e;

void load_palette(pal_type_e pal_type, uint8_t first_palette, uint8_t nb_palettes, palette_color_t* rgb_data, uint8_t bank);

#endif // __PALETTE_H__