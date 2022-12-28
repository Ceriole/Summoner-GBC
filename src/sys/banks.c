#include "banks.h"

DELCARE_STACK(bank_stack, BANK_STACK_SIZE);

void bank_push(UINT8 bank) OLDCALL
{
    bank;
__asm
    // bank_stack++
    ld hl, #_bank_stack
    inc (hl)
    // *bank_stack = _current_bank;
    ld c, (hl)
    inc hl
    ld b, (hl)
    ld a, (#__current_bank)
    ld (bc), a
    // _current_bank = bank;
    ldhl sp, #2
    ld a, (hl)
    ld (#__current_bank), a
    // SWITCH_ROM(bank)
    ld (#0x2000), a
__endasm;
}

void bank_pop() OLDCALL
{
__asm
    // _current_bank = *(bank_stack);
    ld hl, #_bank_stack
    ld c, (hl)
    inc hl
    ld b, (hl)
    ld a, (bc)
    ld (#__current_bank), a
    // SWITCH_ROM(_current_bank);
    ld (#0x2000), a
    // bank_stack--;
    dec hl
    dec (hl)
__endasm;
}