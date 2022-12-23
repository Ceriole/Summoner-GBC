#ifndef __FADE_H__
#define __FADE_H__

#include <gbdk/platform.h>
#include <gb/cgb.h>

#define FADE_STEP_COUNT 6
#define FADE_STEP_END (FADE_STEP_COUNT - 1)

void fade_in(uint8_t fade_delay);
void fade_out(uint8_t fade_delay);
void fade_set(uint8_t fade_step);

#endif // __FADE_H__