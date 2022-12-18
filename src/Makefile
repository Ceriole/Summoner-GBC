PROJECT_NAME = ZGB_TEMPLATE

all: build_gb

# Number of banks (must be a power of 2): A (Automatic), 2, 4, 8, 16, 32...
N_BANKS = A

# Music player: HUGETRACKER(default) or GBT_PLAYER
MUSIC_PLAYER = GBT_PLAYER

# Default hardware sprites size: SPRITES_8x16(default) or SPRITES_8x8
DEFAULT_SPRITES_SIZE = SPRITES_8x16

include $(ZGB_PATH)/src/MakefileCommon

ASE = $(foreach dir,../res,$(notdir $(wildcard $(dir)/*.ase)))
SPRITES_ASE = $(foreach dir,../res/sprites,$(notdir $(wildcard $(dir)/*.ase)))

PNGS += $(ASE:%.ase=%.png)
SPRITES_PNG += $(SPRITES_ASE:%.ase=%.png)

.SECONDARY: $(ASE:.ase=.png) $(SPRITES_ASE:.ase=.png)

%.png: %.ase
	@echo converting aseprite file $<
	$(ASEPRITE_HOME)/Aseprite.exe -b $< --save-file $@

.SECONDEXPANSION:
$(OBJDIR_RES)/%.png.c: $(OBJDIR_RES)/%.png $$(wildcard $(OBJDIR_RES)/%.png.meta)
	@$(PNG2ASSET) $< $(CFLAGSPNG2ASSET) `cat <$<.meta` -b 255 -use_structs -c $@
