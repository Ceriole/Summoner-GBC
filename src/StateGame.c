#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Music.h"

IMPORT_MAP(cerisoft_logo);

DECLARE_MUSIC(cerisoft_theme);

void START() {
	PlayMusic(cerisoft_theme, 1);
	InitScroll(BANK(cerisoft_logo), &cerisoft_logo, 0, 0);
}

void UPDATE() {
}
