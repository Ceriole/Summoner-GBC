include cfg.mk

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
include make/assets.mk
# Set to rgbds v5.1 for building hUGEDriver
RGBDS51_HOME	?= $(RGBDS_HOME)
include make/libs.mk