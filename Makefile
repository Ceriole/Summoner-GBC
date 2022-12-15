###########################################################
# Makefile
# Create rom file from sources, libraries, and assets.
# Written by: @Ceriole
###########################################################

CONFIG			:= cfg.mk

# Check for config file
ifeq ("$(wildcard $(CONFIG))","")
$(error Config file does not exist! Please create one in the same directory as 'Makefile'. See README.md for an example config file.)
else
$(info Loading config file $(CONFIG))
endif

include $(CONFIG)

ifndef GBDK_HOME
$(error GBDK_HOME is not set to the location of GBDK. Example "C:/gbdk")
endif
ifndef RGBDS_HOME
$(error RGBDS_HOME is not set to the location of RGBDS. Example "C:/rgbds")
endif
ifndef ASEPRITE_HOME
$(warning ASEPRITE_HOME is not set to the location of Aseprite. Aseprite files cannot be exported!)
endif
ifndef PY
$(error PY is not set to python executeable! Example "py", "python", "python3")
endif

###########################################################
# VARIABLES
###########################################################

# Suppress console output if $(Q) wasn't defined already.
ifndef ECHO_CMD
Q 				:= @
endif

# MAKE FUNCTIONS ##########################################
# Recursive wildcard: $(call rwildcard, <dir>, <pattern>): Returns all files in a directory including subdirectories
rwildcard		=	$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
getmetafile		=	$(shell cat $(1:$(OBJDIR)/%=%).meta)

# PROJECT DIRECTORIES #####################################
OBJDIR			:= build
SRCDIR			:= src
RESDIR			:= res
LIBDIR			:= lib
TOOLSDIR		:= tools
FONTSDIR		:= $(RESDIR)/fonts
# LIBRARY DIRECTORIES #####################################
HUGEDIR			:= $(LIBDIR)/hUGEDriver
VWFDIR			:= $(LIBDIR)/gb-vwf
HARDWAREINC		:= $(LIBDIR)/hardware.inc
# INCLUDE DIRECTORIES #####################################
HUGEINCDIR		:= $(HUGEDIR)/include
INCDIRS			:= $(SRCDIR) $(OBJDIR) $(HUGEINCDIR)

# EXECUTEABLES ############################################
LCC				:= $(GBDK_HOME)/bin/lcc
RGBASM			:= $(RGBDS_HOME)/rgbasm
PNG2ASSET		:= $(GBDK_HOME)/bin/png2asset
RGB2SDAS		:= $(TOOLSDIR)/rgb2sdas.exe
MAKEFONT		:= $(PY) $(VWFDIR)/make_font.py
ASEPRITE		:= $(ASEPRITE_HOME)/Aseprite.exe -b
ANIMGEN			:= $(PY) $(TOOLSDIR)/animgen.py

# PROJECT PROPERTIES ######################################
# Name of your project, will set the name of the ROM.
PROJECT_NAME	:= SUMMONER
# ROM file extension.
EXT				:= gbc
# ROM flags
ROMFLAGS		:= -Z -yt0x1B -yC -yoA -ya4 -yn"$(PROJECT_NAME)" -yj

# RESOURCE FILES ###########################################
METAFILES		:= $(call rwildcard, $(RESDIR), *.meta)
ASEFILES		:= $(call rwildcard, $(RESDIR), *.ase)
FONTS			:= $(call rwildcard, $(FONTSDIR), *.png)
VWFFILES		:= $(FONTS:%.png=$(OBJDIR)/%.vwf)
ASEIMAGES		:= $(filter $(METAFILES:.meta=), $(ASEFILES:.ase=.png))
ASEANIMS		:= $(filter $(METAFILES:.anim.meta=_anim.c), $(ASEFILES:%.ase=%_anim.c))
IMAGES			:= $(filter $(METAFILES:.meta=), $(filter-out $(FONTS:.vwf=.png) $(ASEIMAGES), $(call rwildcard, $(RESDIR), *.png)))
# SOURCE FILES ############################################
# ROM file
ROMFILENAME		:= $(subst $() $(),_,$(PROJECT_NAME))
BIN				:= $(ROMFILENAME).$(EXT)
# C source files
SRC				:= $(call rwildcard, $(SRCDIR), *.c) $(call rwildcard, $(RESDIR), *.c)
# Assembly source files
ASM				:= $(call rwildcard, $(SRCDIR), *.s)
# Project object files
OBJ				:= $(addprefix $(OBJDIR)/, $(IMAGES:.png=.o) $(ASEIMAGES:.png=.o) $(ASEANIMS:.c=.o) $(SRC:.c=.o) $(ASM:.s=.o) $(HUGEDIR)/hUGEDriver.obj.o $(LIBDIR)/vwf_gbdk.obj.o)
# Generated dependency files
DEPS			:= $(OBJ:.o=.d)

# FLAGS ###################################################
# Comment the below line out to disable debug file output.
DEBUGFLAG		?= -debug
INCFLAGS		:= $(addprefix -I, $(INCDIRS))
CFLAGS			:= $(INCFLAGS) -Wf-MMD $(DEBUGFLAG)
LCCFLAGS		:= -msm83:gb -Wl-j -Wb-ext=.rel -Wb-v $(addprefix -Wm, $(ROMFLAGS)) -autobank
RGBASMFLAGS		:= -Wno-obsolete -DGBDK $(addprefix -i, $(HUGEDIR) $(VWFDIR) $(LIBDIR) $(OBJDIR))
RGBCONVFLAGS	:= -b255

# MAKEFILE DEBUG INFO #####################################

ifdef ECHO_DATA
$(info Echoing commands.)
$(info Target rom: $(BIN))
$(info C sources: $(SRC))
$(info ASM sources: $(ASM))
$(info Meta files: $(METAFILES))
$(info Aseprite files: $(ASEFILES))
$(info Animation files: $(ASEANIMS))
$(info PNG files: $(IMAGES))
$(info Font files: $(FONTS))
$(info Object files: $(OBJ))
$(info Dependency files: $(DEPS))
endif

###########################################################
# RULES
###########################################################

# Non-file rules
.PHONY: all clean cleanObj cleanBin
# Enable secondary expansion
.SECONDEXPANSION:
ifneq ($(Q),@)
# Disable deletion of intermediate file
.SECONDARY:
endif

# Include dependency files
-include $(DEPS)

# All
all: $(BIN)

# SOURCES #################################################
# Compile .c files
$(OBJDIR)/%.o: %.c
	@echo 'Compiling $<'
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(CFLAGS) -c -o $@ $< 

# Compile .s (assembly) files
$(OBJDIR)/%.o: %.s
	@echo 'Compiling $<'
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(CFLAGS) -c -o $@ $< 

# Compile generated .c files
$(OBJDIR)/%.o: $(OBJDIR)/%.c
	@echo 'Compiling resource file $<'
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(CFLAGS) -c -o $@ $<

# If needed, compile .c into .s assembly files.
# Not normally required if .c is directly compiled into .o files.
$(OBJDIR)/%.s: %.c
	@echo 'Compiling $<'
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(CFLAGS) -S -o $@ $<

# Rule to catch generated header files
%.h:

# BINARY ##################################################
$(PROJECT_NAME).$(EXT): $(OBJ)
	@echo 'Making ROM $@'
	$(Q)$(LCC) $(LCCFLAGS) $(CFLAGS) $^ -o $@ 

# RESOURCES ###############################################
# Export asesprite files only if Aseprite is set.
ifdef ASEPRITE_HOME
$(OBJDIR)/$(RESDIR)/%.png: $(RESDIR)/%.ase
	@echo 'Exporting $< to $@'
	@mkdir -p $(dir $@)
	$(Q)$(ASEPRITE) $< $(call getmetafile, $<) --sheet $@ >/dev/null
$(OBJDIR)/$(RESDIR)/%.json: $(RESDIR)/%.ase
	@echo 'Exporting $< animations to $@'
	@mkdir -p $(dir $@)
	$(Q)$(ASEPRITE) $< $(call getmetafile, $@) --list-tags --filename-format {title}-{tag}-{tagframe}.{extension} --format json-array --data $@
$(OBJDIR)/$(RESDIR)/%_anim.c $(OBJDIR)/$(RESDIR)/%_anim.h: $(OBJDIR)/$(RESDIR)/%.json
	@echo 'Converting $< animations to $@'
	@mkdir -p $(dir $@)
	$(Q)$(ANIMGEN) $< $(call getmetafile, $(<:.json=.anim)) -o $@
endif

# Convert png files into source files
$(OBJDIR)/$(RESDIR)/%.c $(OBJDIR)/$(RESDIR)/%.h: $(OBJDIR)/$(RESDIR)/%.png
	@echo 'Converting $< to $@'
	@mkdir -p $(dir $@)
	$(Q)$(PNG2ASSET) $< $(call getmetafile, $<) -c $@

$(OBJDIR)/$(RESDIR)/%.c $(OBJDIR)/$(RESDIR)/%.h: $(RESDIR)/%.png
	@echo 'Converting $< to $@'
	@mkdir -p $(dir $@)
	$(Q)$(PNG2ASSET) $< $(call getmetafile, $<) -c $@

# Generate vwf font files
$(OBJDIR)/$(FONTSDIR)/%.vwf: $(FONTSDIR)/%.png
	@echo 'Generating font $@'
	@mkdir -p $(dir $@)
	$(Q)$(MAKEFONT) $< $@

# LIBRARIES ###############################################
# Convert RGBDS .obj files into SDAS .o files
$(OBJDIR)/%.obj.o: $(OBJDIR)/%.obj $(RGB2SDAS)
	@echo 'Converting $< into SDAS...'
	@mkdir -p $(dir $@)
	$(Q)$(RGB2SDAS) $(RGBCONVFLAGS) $<
# rgb2sdas makes a incompatible file, just due to the O flag. The below command replaces '-mgbz80' (SDCC <= 4.1.0) with '-msm83' (SDCC >= 4.2.0)
	$(Q)sed -i 's/-mgbz80/-msm83/' $@

# Make VWF require font files.
$(OBJDIR)/$(LIBDIR)/vwf_gbdk.obj: $(VWFFILES)

# Compile RGBDS .asm assembly files to RGBDS .obj files
$(OBJDIR)/%.obj: %.asm
	@echo 'Compiling (RGBDS) $<'
	@mkdir -p $(dir $@)
	$(Q)$(RGBASM) $(RGBASMFLAGS) $< -o $@


# CLEAN ###################################################
clean: cleanObj cleanBin

cleanObj:
	@rm -rf $(OBJDIR)

cleanBin:
	@rm -rf $(ROMFILENAME).*