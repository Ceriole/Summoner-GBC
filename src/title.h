#ifndef __TITLE_H__
#define __TITLE_H__

#include <gbdk/platform.h>

void title_init(void) BANKED;
BANKREF_EXTERN(title_init)
void title_sequence(void) BANKED;
BANKREF_EXTERN(title_sequence)
void title_loop(void) BANKED;
BANKREF_EXTERN(title_loop)

#endif // __TITLE_H__