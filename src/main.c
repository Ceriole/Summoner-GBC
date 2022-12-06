#include <gb/gb.h>
#include <stdint.h>

#include "asset.h"

void main(void)
{
    while(1)
    {
        
		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}