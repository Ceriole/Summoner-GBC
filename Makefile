include cfg.mk

OBJDIR			= build
SRCDIR			= src
RESDIR			= res
LIBDIR			= lib
TOOLSDIR		= tools

# Name of your project, will set the name of your ROM.
PROJECT_NAME	:= SUMMONER

LIBS			:= $(OBJDIR)/$(LIBDIR)/hUGEDriver/hUGEDriver.obj.o # $(OBJDIR)/$(LIBDIR)/gb-vwf/vwf.obj.o # TODO

include gbdk.mk
# Set to rgbds v5.1 for building hUGEDriver
include libs.mk