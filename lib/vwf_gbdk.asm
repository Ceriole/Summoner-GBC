INCLUDE "hardware.inc/hardware.inc"

MACRO lb
    assert (\2) < 256
    assert (\3) < 256
    ld \1, (\2) << 8 | (\3)
ENDM

TEXT_WIDTH_TILES equ 18
TEXT_HEIGHT_TILES equ 8
EXPORT TEXT_WIDTH_TILES
EXPORT TEXT_HEIGHT_TILES
TEXT_Y_OFF equ 1
TEXT_X_OFF equ FLOOR(SCRN_X_B / 2) - FLOOR(TEXT_WIDTH_TILES / 2)

; Charset IDs increase 2 by 2
CHARSET_0  equs "res/fonts/BaseSeven.vwf"
CHARSET_2  equs "res/fonts/BaseSevenBold_vx8.vwf"
CHARSET_16 equs "res/fonts/optix.vwf"
CHARSET_18 equs "res/fonts/optixBold.vwf"
NB_CHARSETS equ 10

SKIP_HELD_KEYS equ PADF_B
SKIP_PRESSED_KEYS equ PADF_A

EXPORT_CONTROL_CHARS equ 1

; joypad 1, 2, 3, 4
JOYPAD_NUM equ 1
hPressedKeys equs "_joys + {JOYPAD_NUM}"
hHeldKeys equs "_pressed_joys + {JOYPAD_NUM}"
hCurROMBank equs "__current_bank"

PRINT "wow: {TEXT_X_OFF}"

SECTION UNION "9C00 Tilemap", VRAM[_SCRN1]
    ds SCRN_VX_B * 3
    ds 1
vText::
    ds TEXT_WIDTH_TILES + 2

INCLUDE "gb-vwf/vwf.asm"