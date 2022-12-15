#include <gbdk/platform.h>
#include <gb/crash_handler.h>
#include <gb/gb.h>

#include "title.h"
#include "sys/screens.h"
#include "sys/input.h"

#include "hUGEDriver.h"

void main(void)
{
	if(!DEVICE_SUPPORTS_COLOR)
		screen_cgb_required(); // Catch if the system is not a color gameboy
	else
	{
		input_init(1);
		CRITICAL {
			add_VBL((int_handler) hUGE_dosound);
		}
		
		cpu_fast(); // Only available on CGB (hardware emulated)

		title_sequence();
	}
}