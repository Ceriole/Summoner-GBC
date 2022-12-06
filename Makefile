GBDK_HOME		:= D:/gbdk/
# Aseprite executeable for 
ASEPRITE_HOME	:= D:/SteamLibrary/steamapps/common/Aseprite

OBJDIR			= build
SRCDIR			= src
RESDIR			= res
LIBDIR			= lib

# Name of your project, will set the name of your ROM.
PROJECT_NAME	:= SUMMONER
# Run "rgbfix --mbc-type help" for possible MBC types
MBC				:= ROM
# Target should be a combination of DMG, CGB and SGB
TARGETS			:= CGB

LIBS			:= $(OBJDIR)/$(LIBDIR)/hUGEDriver/hUGEDriver.obj.o

include make/gbdk.mk
# Set to rgbds v6.0 for the newest rgbgfx
RGBDS_HOME		:= D:/RGBDS/6.0
include make/assets.mk
# Set to rgbds v5.1 for building hUGEDriver
RGBDS_HOME		:= D:/RGBDS/5.1
include make/libs.mk