#ifndef __MATH_H__
#define __MATH_H__

#include <stdint.h>

uint16_t shift_right(uint16_t a, uint16_t b);

#define U_LESS_THAN(A, B) ((A) - (B) & 0x8000u)

#define DISTANCE(A, B) (U_LESS_THAN(A, B) ? (B - A) : (A - B))

#define SET_BIT(N, POS)   N |=   1 << POS
#define UNSET_BIT(N, POS) N &= ~(1 << POS)
#define GET_BIT(N, POS)   (1 & shift_right(N, POS))

#define SET_BIT_MASK(N, MASK) N |= MASK
#define UNSET_BIT_MASK(N, MASK) N &= ~MASK
#define GET_BIT_MASK(N, MASK) (N & MASK)

#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

#endif // __MATH_H__