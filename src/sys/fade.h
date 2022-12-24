#ifndef __FADE_H__
#define __FADE_H__

#include <gbdk/platform.h>
#include <gb/cgb.h>
#include "palette.h"

#define FADE_STEP_COUNT 6
#define FADE_STEP_END (FADE_STEP_COUNT - 1)

void fade_in(uint8_t fade_delay);
void fade_out(uint8_t fade_delay);
void fade_set(uint8_t fade_step);

void fade_enable_pal(pal_type_e pal_type, uint8_t pal_idx, uint8_t enable_fade);
void fade_enable_pals(pal_type_e pal_type, uint8_t enable_fade);
void fade_enable_all(uint8_t enable_fade);
inline void fade_enable_isolate(pal_type_e pal_type, uint8_t pal_idx)
{
    fade_enable_pals(pal_type, FALSE);
    fade_enable_pal(pal_type, pal_idx, TRUE);
}

#endif // __FADE_H__