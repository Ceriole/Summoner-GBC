#ifndef __HUGE_BANKED_H__
#define __HUGE_BANKED_H__

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#include "hUGEDriver.h"

void hUGE_banked_init(const hUGESong_t * song, uint8_t song_bank) CRITICAL NONBANKED;
void hUGE_banked_dosound(void) CRITICAL NONBANKED;

#endif // __HUGE_BANKED_H__