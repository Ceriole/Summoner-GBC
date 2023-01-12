#include <gb/gb.h>
#include <gb/cgb.h>

void window_set_y(uint8_t win_y)
{
    WY_REG = win_y;
    LYC_REG = win_y - 1;
    if(win_y < SCREENHEIGHT)
        SHOW_WIN;
    else {
        HIDE_WIN;
        LYC_REG = (DEVICE_SCREEN_HEIGHT + 2) * 8;
    }
}
