
#include <gbdk/platform.h>
#include <gb/gb.h>
#include "hUGEDriver.h"

#pragma bank 0

static uint8_t huge_song_bank;

void hUGE_banked_init(const hUGESong_t * song, uint8_t song_bank) CRITICAL NONBANKED
{
    uint8_t save = _current_bank;
    huge_song_bank = song_bank;
    SWITCH_ROM(huge_song_bank);
    hUGE_init(song);
    SWITCH_ROM(save);
}

void hUGE_banked_dosound(void) CRITICAL NONBANKED
{
    uint8_t save = _current_bank;
    SWITCH_ROM(huge_song_bank);
    hUGE_dosound();
    SWITCH_ROM(save);
}