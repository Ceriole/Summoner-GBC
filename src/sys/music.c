
#pragma bank 0

#include <gbdk/platform.h>
#include <gb/gb.h>
#include "hUGEDriver.h"
#include "banks.h"

uint8_t music_paused = TRUE;
const hUGESong_t *current_track, *last_track = 0;
uint8_t current_track_bank;

void music_callback() NONBANKED
{
	if (music_paused) 
			return;

	PUSH_BANK(current_track_bank);
	hUGE_dosound();
	POP_BANK;
}

void music_play(const hUGESong_t* track, uint8_t bank) NONBANKED
{
	if(track != last_track) {
		last_track = track;
		NR52_REG = 0x80;
		NR51_REG = 0xFF;
		NR50_REG = 0x77;

		music_paused = TRUE;
		current_track = track; current_track_bank = bank;
		uint8_t __save = _current_bank;
		SWITCH_ROM(current_track_bank);
		hUGE_init(current_track);
		SWITCH_ROM(__save);
		music_paused = FALSE;
	}
}

void music_mute(uint8_t mute) {
	hUGE_mute_channel(HT_CH1, mute);
	hUGE_mute_channel(HT_CH2, mute);
	hUGE_mute_channel(HT_CH3, mute);
	hUGE_mute_channel(HT_CH4, mute);
}