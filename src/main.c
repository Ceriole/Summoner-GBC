#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#include "asset.h"

#define TITLE_MAP_WIDTH DEVICE_SCREEN_WIDTH
#define TITLE_MAP_HEIGHT DEVICE_SCREEN_HEIGHT
#define TITLE_NUM_TILES (sizeof_ASSET(title) / 16)

ASSET(title, "title.chr");
ASSET(title_map, "title.map");
ASSET(title_attr, "title.attrmap");

ASSET(title_pal, "title.pal");

void main(void)
{
	set_bkg_palette(BKGF_CGB_PAL0, sizeof_ASSET(title_pal) / 4, title_pal);

	set_bkg_data(0u, TITLE_NUM_TILES, title);
	/* Select VRAM bank 1 */
	VBK_REG = VBK_ATTRIBUTES;
	/* Set attributes */
	set_bkg_tiles(0, 0, TITLE_MAP_WIDTH, TITLE_MAP_HEIGHT, title_attr);

	/* Select VRAM bank 1 */
	VBK_REG = VBK_TILES;
	/* Set attributes */
	set_bkg_tiles(0, 0, TITLE_MAP_WIDTH, TITLE_MAP_HEIGHT, title_map);

	SHOW_BKG;
	enable_interrupts();
	DISPLAY_ON;

	while(1)
	{
		wait_vbl_done();
	}
}