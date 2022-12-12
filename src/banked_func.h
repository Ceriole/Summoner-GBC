#ifndef __BANKED_FUNC_H__
#define __BANKED_FUNC_H__

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#define BANKED_DATA_FUNC_EXTERN(FUNCNAME, ...) void FUNCNAME(__VA_ARGS__, uint8_t bank) NONBANKED
#define BANKED_DATA_FUNC(FUNCNAME, FUNCCALL, ...) \
    void FUNCNAME(__VA_ARGS__, uint8_t bank) NONBANKED \
    { \
        uint8_t save = _current_bank; \
        SWITCH_ROM(bank); \
        FUNCCALL; \
        SWITCH_ROM(save); \
    }

#endif // __BANKED_FUNC_H__