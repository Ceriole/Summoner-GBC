#include <gbdk/platform.h>
#include <gb/crash_handler.h>
#include <gb/gb.h>

#include "title.h"
#include "sys/screens.h"
#include "sys/input.h"
#include "sys/music.h"

void LCD_isr() NONBANKED {
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


void main(void)
{
	CRITICAL
	{
		TMA_REG = DEVICE_SUPPORTS_COLOR ? 120U : 0xBCU;
		TAC_REG = 0x04u;

		add_low_priority_TIM(music_callback);
		STAT_REG |= STATF_MODE00;
		add_LCD(LCD_isr);
	}
	music_init;
	set_interrupts(VBL_IFLAG | TIM_IFLAG | LCD_IFLAG);
	if(!DEVICE_SUPPORTS_COLOR)
		screen_cgb_required(); // Catch if the system is not a color gameboy
	else
	{
		cpu_fast(); // Only available on CGB (hardware emulated)
			
		input_init(1);

		screen_studio();
		title_sequence();
	}
}