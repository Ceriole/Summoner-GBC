#include <gbdk/platform.h>

#ifndef __TITLE_H__
#define __TITLE_H__

void title_init(void) BANKED;
BANKREF_EXTERN(title_init)
void title_sequence(void) BANKED;
BANKREF_EXTERN(title_sequence)
void title_loop(void) BANKED;
BANKREF_EXTERN(title_loop)

#endif // __TITLE_H__