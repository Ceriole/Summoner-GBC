#ifndef __INPUT_H__
#define __INPUT_H__

#include <gbdk/platform.h>

extern joypads_t joys, pressed_joys;

void input_init(const uint8_t npads) NONBANKED;
void input_update(void) NONBANKED;

#endif // __INPUT_H__