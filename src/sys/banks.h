#ifndef __BANKS_H__
#define __BANKS_H__

#include "stack.h"

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>


#define BANK_STACK_SIZE 8

extern UINT8* bank_stack;

void bank_push(UINT8 bank) OLDCALL;
void bank_pop() OLDCALL;

#define PUSH_BANK(BANK) bank_push(BANK)
#define POP_BANK bank_pop()
#define REFRESH_BANK SWITCH_ROM(_current_bank)

#define BANKED_DATA_FUNC_EXTERN(FUNCNAME, ...) void FUNCNAME(__VA_ARGS__, uint8_t bank) CRITICAL NONBANKED
#define BANKED_DATA_FUNC(FUNCNAME, FUNCCALL, ...) \
    void FUNCNAME(__VA_ARGS__, uint8_t bank) CRITICAL NONBANKED \
    { \
        PUSH_BANK(bank); \
        FUNCCALL; \
        POP_BANK; \
    }

#endif // __BANKS_H__