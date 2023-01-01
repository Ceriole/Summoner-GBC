// Bank pragma for autobanking
#pragma bank 255

#include "title.h"

#include "sys/music.h"

#include "res/screens/title_screen.h"
#include "res/sprites/bluefire.h"
#include "res/sprites/bluefire_anim.h"

#include "gfx/sprite.h"
#include "gfx/banked_gfx.h"
#include "gfx/fade.h"
#include "gfx/palette.h"

#include "sys/input.h"

DECLARE_MUSIC(mus_title);

#define PENTA_Y_POS 5
#define PENTA_HEIGHT 111
#define FLAME_POS_LENGTH 256
#define FLAME_COUNT 5
#define FLAME_KEY_OFFET (FLAME_POS_LENGTH / FLAME_COUNT)
#define FLAME_APPEAR_DELAY 40
#define PENTA_FADE_DELAY 20
#define TITLE_FADE_DELAY 20

const static uint8_t flame_x_positions[FLAME_POS_LENGTH] = { 57u, 58u, 60u, 61u, 62u, 63u, 64u, 65u, 66u, 67u, 69u, 70u, 71u, 72u, 73u, 75u, 76u, 77u, 78u, 80u, 81u, 82u, 83u, 85u, 86u, 87u, 89u, 90u, 91u, 92u, 94u, 95u, 96u, 97u, 99u, 100u, 101u, 102u, 104u, 105u, 106u, 107u, 108u, 110u, 111u, 112u, 113u, 114u, 115u, 116u, 117u, 118u, 119u, 120u, 121u, 122u, 123u, 124u, 125u, 126u, 127u, 128u, 129u, 129u, 130u, 131u, 132u, 132u, 133u, 133u, 134u, 135u, 135u, 136u, 136u, 137u, 137u, 138u, 138u, 138u, 139u, 139u, 139u, 139u, 140u, 140u, 140u, 140u, 140u, 140u, 140u, 140u, 140u, 140u, 140u, 140u, 139u, 139u, 139u, 139u, 138u, 138u, 138u, 137u, 137u, 136u, 136u, 135u, 135u, 134u, 134u, 133u, 132u, 132u, 131u, 130u, 129u, 129u, 128u, 127u, 126u, 125u, 124u, 123u, 123u, 122u, 121u, 120u, 119u, 118u, 116u, 115u, 114u, 113u, 112u, 111u, 110u, 109u, 107u, 106u, 105u, 104u, 103u, 101u, 100u, 99u, 98u, 96u, 95u, 94u, 93u, 91u, 90u, 89u, 87u, 86u, 85u, 84u, 82u, 81u, 80u, 79u, 77u, 76u, 75u, 74u, 72u, 71u, 70u, 69u, 68u, 66u, 65u, 64u, 63u, 62u, 61u, 60u, 59u, 58u, 57u, 56u, 55u, 54u, 53u, 52u, 51u, 50u, 49u, 48u, 47u, 47u, 46u, 45u, 44u, 44u, 43u, 43u, 42u, 41u, 41u, 40u, 40u, 39u, 39u, 38u, 38u, 38u, 37u, 37u, 37u, 37u, 36u, 36u, 36u, 36u, 36u, 36u, 36u, 36u, 36u, 36u, 36u, 36u, 37u, 37u, 37u, 37u, 38u, 38u, 38u, 39u, 39u, 40u, 40u, 41u, 41u, 42u, 42u, 43u, 44u, 44u, 45u, 46u, 47u, 47u, 48u, 49u, 50u, 51u, 52u, 53u, 53u, 54u, 55u, 56u };
const static uint8_t flame_y_positions[FLAME_POS_LENGTH] = { 29u, 28u, 27u, 27u, 26u, 26u, 25u, 24u, 24u, 23u, 23u, 22u, 22u, 21u, 21u, 21u, 20u, 20u, 20u, 20u, 19u, 19u, 19u, 19u, 19u, 19u, 19u, 19u, 19u, 19u, 19u, 19u, 20u, 20u, 20u, 20u, 21u, 21u, 21u, 22u, 22u, 23u, 23u, 24u, 24u, 25u, 25u, 26u, 27u, 27u, 28u, 29u, 30u, 30u, 31u, 32u, 33u, 34u, 35u, 36u, 36u, 37u, 38u, 39u, 40u, 41u, 43u, 44u, 45u, 46u, 47u, 48u, 49u, 50u, 52u, 53u, 54u, 55u, 56u, 58u, 59u, 60u, 61u, 63u, 64u, 65u, 66u, 68u, 69u, 70u, 72u, 73u, 74u, 75u, 77u, 78u, 79u, 80u, 82u, 83u, 84u, 85u, 87u, 88u, 89u, 90u, 91u, 93u, 94u, 95u, 96u, 97u, 98u, 99u, 100u, 101u, 102u, 103u, 104u, 105u, 106u, 107u, 108u, 109u, 110u, 111u, 112u, 112u, 113u, 114u, 115u, 115u, 116u, 116u, 117u, 118u, 118u, 119u, 119u, 120u, 120u, 121u, 121u, 121u, 122u, 122u, 122u, 122u, 123u, 123u, 123u, 123u, 123u, 123u, 123u, 123u, 123u, 123u, 123u, 123u, 122u, 122u, 122u, 122u, 121u, 121u, 121u, 120u, 120u, 119u, 119u, 118u, 118u, 117u, 117u, 116u, 115u, 115u, 114u, 113u, 112u, 112u, 111u, 110u, 109u, 108u, 107u, 106u, 106u, 105u, 104u, 103u, 102u, 101u, 99u, 98u, 97u, 96u, 95u, 94u, 93u, 92u, 90u, 89u, 88u, 87u, 86u, 84u, 83u, 82u, 81u, 79u, 78u, 77u, 76u, 74u, 73u, 72u, 70u, 69u, 68u, 67u, 65u, 64u, 63u, 62u, 60u, 59u, 58u, 57u, 55u, 54u, 53u, 52u, 51u, 49u, 48u, 47u, 46u, 45u, 44u, 43u, 42u, 41u, 40u, 39u, 38u, 37u, 36u, 35u, 34u, 33u, 32u, 31u, 30u, 30u };
const static int8_t penta_wobble_tbl[32 * 3] = {
	0, 2, 3, 4, 4, 4, 3, 2, 0, -2, -3, -4, -4, -4, -3, -2, 0, 2, 3, 4, 4, 4, 3, 2, 0, -2, -3, -4, -4, -4, -3, -2,
	0, 1, 2, 2, 2, 2, 2, 1, 0, -1, -2, -2, -2, -2, -2, -1, 0, 1, 2, 2, 2, 2, 2, 1, 0, -1, -2, -2, -2, -2, -2, -1,
	0, 0, 1, 1, 1, 1, 1, 0, 0, 0, -1, -1, -1, -1, -1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, -1, -1, -1, -1, -1, 0
};
enum TITLE_STATE_E {
	T_ST_FIREINTRO,
	T_ST_FIRESPIN,
	T_ST_FADEPENTA,
	T_ST_FADETITLE,
	T_ST_WAIT,
	T_ST_END
} state = T_ST_FIREINTRO;
uint8_t timer = 0;
sprite_t flame_spr[FLAME_COUNT];
sprite_t* curr_spr;
uint8_t current_fire_idx = 0, enable_penta_wobble = FALSE, penta_wobble_step = 0;
uint16_t penta_wobble_update_timer;
const int8_t* penta_wobble = penta_wobble_tbl;

BANKREF(title_init)
void title_init(void) BANKED
{
	SPRITES_8x16;

	load_palette(PAL_TYPE_BG, BKGF_CGB_PAL0, title_screen_PALETTE_COUNT, title_screen_palettes, BANK(title_screen));
	load_palette(PAL_TYPE_OBJ, OAMF_CGB_PAL0, bluefire_PALETTE_COUNT, bluefire_palettes, BANK(bluefire));
	fade_enable_pal(PAL_TYPE_OBJ, OAMF_CGB_PAL0, FALSE);
	fade_set(0);

	set_banked_sprite_data(0u, bluefire_TILE_COUNT, bluefire_tiles, BANK(bluefire));

	set_banked_bkg_data(0u, title_screen_TILE_COUNT, title_screen_tiles, BANK(title_screen));
	/* Select VRAM bank 1 */
	rVBK = VBK_ATTRIBUTES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, title_screen_WIDTH / title_screen_TILE_W, title_screen_HEIGHT / title_screen_TILE_H, title_screen_map_attributes, BANK(title_screen));

	/* Select VRAM bank 1 */
	rVBK = VBK_TILES;
	/* Set attributes */
	set_banked_bkg_tiles(0, 0, title_screen_WIDTH / title_screen_TILE_W, title_screen_HEIGHT / title_screen_TILE_H, title_screen_map, BANK(title_screen));
}

BANKREF(title_sequence)
void title_sequence(void) BANKED
{
    title_init();
	MUSIC_PLAY(&mus_title, BANK(mus_title));
    title_loop();
}

void title_init_flames()
{
	uint8_t flame_pos_idx = 0;
	curr_spr = flame_spr;
	for(uint8_t fi = 0; fi < FLAME_COUNT; fi++)
	{
		create_sprite(curr_spr, flame_x_positions[flame_pos_idx], flame_y_positions[flame_pos_idx], 0u, bluefire_anim, bluefire_metasprites);
		flame_pos_idx += FLAME_KEY_OFFET;
		curr_spr->hide = TRUE;
		curr_spr++;
	}
	flame_pos_idx = 0;
}

void title_render_flames()
{
	uint8_t oam_idx = 0;
	curr_spr = flame_spr;
	for(uint8_t fi = 0; fi < FLAME_COUNT; fi++)
	{
		spr_update(curr_spr);
		oam_idx += spr_render(curr_spr, oam_idx);
		curr_spr++;
	}
}

void title_wobble_lcd_isr()
{
	rSCX = penta_wobble[rLY & 15u];
}

BANKREF(title_loop)
void title_loop(void) BANKED
{
	title_init_flames();
	while(state != T_ST_END)
	{
		timer++;
		switch (state)
		{
		case T_ST_FIREINTRO:
			if(timer == FLAME_APPEAR_DELAY)
			{
				timer = 0;
				if(current_fire_idx > 0)
					flame_spr[current_fire_idx - 1].flash = FALSE;
				flame_spr[current_fire_idx].hide = FALSE;
				flame_spr[current_fire_idx].flash = TRUE;
				current_fire_idx++;
				if(current_fire_idx > FLAME_COUNT)
				{
					flame_spr[current_fire_idx - 1].flash = FALSE;
					state = T_ST_FIRESPIN;
					current_fire_idx = 0;
				}
			}
			break;
		case T_ST_FIRESPIN:
			current_fire_idx++;
			curr_spr = flame_spr;
			uint8_t fire_pos_idx = current_fire_idx;
			for(uint8_t fi = 0; fi < FLAME_COUNT; fi++)
			{
				spr_set_pos(curr_spr, flame_x_positions[fire_pos_idx], flame_y_positions[fire_pos_idx]);
				fire_pos_idx += FLAME_KEY_OFFET;
				curr_spr++;
			}
			if(current_fire_idx != 0)
				break;
			fade_enable_isolate(PAL_TYPE_BG, BKGF_CGB_PAL0);
			fade_in(PENTA_FADE_DELAY);
			CRITICAL {
				rSTAT = STATF_MODE00; // turn on H blank ISR
				add_LCD(title_wobble_lcd_isr);
			}
			state = T_ST_FADEPENTA;
			break;
		case T_ST_FADEPENTA:
			if(fade_running())
			{
				penta_wobble = &penta_wobble_tbl[(uint8_t)(sys_time >> 2) & 15u] + (32 * (fade_step >> 1));
				break;
			}
			CRITICAL {
				rSTAT &= ~STATF_MODE00; // turn of H blank ISR
				remove_LCD(title_wobble_lcd_isr);
			}
			rSCX = 0;
			fade_enable_isolate(PAL_TYPE_BG, BKGF_CGB_PAL1);
			fade_in(TITLE_FADE_DELAY);
			state = T_ST_FADETITLE;
			break;
		case T_ST_FADETITLE:
			if(fade_running())
				break;
			state = T_ST_WAIT;
			break;
		case T_ST_WAIT:
			if(joys.joy0 & 0xF0) // any button pressed
				state = T_ST_END;
			break;
		}
		title_render_flames();
		wait_vbl_done();
	}
	fade_enable_all(TRUE);
	fade_out(TITLE_FADE_DELAY);
	MUSIC_STOP;
	while(fade_running()) wait_vbl_done();
}