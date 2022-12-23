#include <gbdk/platform.h>
#include <gb/crash_handler.h>
#include <gb/gb.h>

#include "title.h"
#include "sys/screens.h"
#include "sys/input.h"
#include "sys/music.h"

void LCD_isr() NONBANKED
{
	if (LYC_REG == 0) {
		if (WY_REG == 0) {
			HIDE_SPRITES;
		} else {
			SHOW_SPRITES;
			LYC_REG = WY_REG - 1;
		}
	} else {
		HIDE_SPRITES;
		LYC_REG = 0;
	}
}

void VBL_global() NONBANKED
{
	input_update();
}

void main(void)
{
	for (uint8_t i = 4; i != 0; i--) {
		wait_vbl_done();
	}
	input_init(1);
	CRITICAL
	{
		TMA_REG = DEVICE_SUPPORTS_COLOR ? 120U : 0xBCU;
		TAC_REG = 0x04u;

		add_low_priority_TIM(music_callback);

		add_VBL(VBL_global);

		STAT_REG |= 0x40;
		add_LCD(LCD_isr);
	}
	music_init;
	LCDC_REG |= LCDCF_OBJ16 | LCDCF_OBJON | LCDCF_BGON;
	set_interrupts(VBL_IFLAG | TIM_IFLAG | LCD_IFLAG);
	WY_REG = 160u;
	DISPLAY_ON;
	if(!DEVICE_SUPPORTS_COLOR)
	{
		screen_cgb_required(); // Catch if the system is not a color gameboy
	}
	else
	{
		cpu_fast(); // Only available on CGB (hardware emulated)
		
		screen_studio();
		title_sequence();
	}
}