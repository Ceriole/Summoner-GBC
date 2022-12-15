#include "input.h"

#include <gbdk/platform.h>

joypads_t joys, pressed_joys;
static joypads_t last_joys;

void input_init(const uint8_t npads) NONBANKED
{
    joypad_init(npads, &joys);
    joypad_init(npads, &pressed_joys);
}

void input_update(void) NONBANKED
{
    last_joys = joys;
    joypad_ex(&joys);
    for(uint8_t joy = 0; joy < joys.npads; joy++)
    {
        // pressed = current && !last
        pressed_joys.joypads[joy] = joys.joypads[joy] & (~last_joys.joypads[joy]);
    }
}