#ifndef __STACK_H__
#define __STACK_H__

#include <gb/gb.h>

#define DELCARE_STACK(NAME, STACK_SIZE) UINT8 NAME##STACK[STACK_SIZE]; UINT8* NAME = NAME##STACK - 1
#define DECLARE_STAKCK_AND_PUSH(NAME, STACK_SIZE, ELEM) UINT8 NAME##STACK[STACK_SIZE] = {ELEM}; UINT8* NAME = NAME##STACK

#define StackPeek(STACK) (*STACK)

#define StackPush(STACK, ELEM) (*(++STACK) = ELEM)
#define StackPop(STACK) (*(STACK--))
#define StackClear(NAME) NAME = NAME##STACK - 1

#endif // __STACK_H__