.PHONY: all rom clean cleanRom cleanBuild

rwildcard	=	$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

ifndef SRCDIR
$(error SRCDIR is not set. Example "src")
endif
ifndef OBJDIR
$(error OBJDIR is not set. Example "build")
endif
ifndef GBDK_HOME
$(error GBDK_HOME is not set to the location of GBDK. Example "D:/gbdk")
endif

LCC				= $(GBDK_HOME)/bin/lcc

ifndef PROJECT_NAME
$(error PROJECT_NAME is not set to the name of your rom.)
endif
ifndef MBC
$(error MBC is not set. Should be set to the MBC name or value you want. Example "MBC5+RAM+BATTERY")
endif
ifndef TARGETS
$(error TARGETS is not set. Should be a combination of DMG SGB CGB)
endif
ifneq ($(filter-out DMG SGB CGB,$(TARGETS)),)
$(error TARGETS should be a combination of DMG SGB CGB, unknown: $(filter-out DMG SGB CGB,$(TARGETS)))
endif

SRC				= $(call rwildcard, $(SRCDIR), *.c) # $(shell find $(SRCDIR)/ -type f -name '*.c')
ASM				= $(call rwildcard, $(SRCDIR), *.s) # $(shell find $(SRCDIR)/ -type f -name '*.s')
OBJ				= $(patsubst %, $(OBJDIR)/%.o, $(ASM) $(SRC))

LCCFLAGS		= -msm83:gb -I. -I$(SRCDIR) -Wm-Z -Wm-yn"$(PROJECT_NAME)" -Wm-yj -debug

ROM_EXTENSION	:= gb

PROJECT_NAME := $(subst $() $(),_,$(PROJECT_NAME))

ifeq ($(filter CGB,$(TARGETS)),) # Not targeting CGB, so disable CGB features
	LCCFLAGS += -DCGB=0
else
	LCCFLAGS += -DCGB=1
	ifeq ($(filter DMG,$(TARGETS))$(filter SGB,$(TARGETS)),) # Check if not targeting both CGB and DMG
		LCCFLAGS += -Wm-yC
	else
		LCCFLAGS += -Wm-yc
	endif
    ROM_EXTENSION := gbc
endif
ifeq ($(filter SGB,$(TARGETS)),) # Not targeting SGB, so disable SGB features
	LCCFLAGS += -DSGB=0
else # Targeting SGB as well
	LCCFLAGS += -DSGB=1
	LCCFLAGS += -Wm-ys
endif
ifneq ($(findstring RAM,$(MBC)),)
	LCCFLAGS += -Wm-yt2
endif

Q ?= @

all: rom

rom: $(PROJECT_NAME).$(ROM_EXTENSION)

$(OBJDIR)/%.c.o: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.s.o: %.s
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.c.d: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(LCCFLAGS) -c -o $@ $< -Wp-MM

$(OBJDIR)/%.s.d: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(LCCFLAGS) -c -o $@ $< -Wp-MM

include $(OBJ:.o=.d)

$(PROJECT_NAME).$(ROM_EXTENSION): $(LIBS) $(OBJ)
	@echo Making rom $@
	$(Q)$(LCC) $(LCCFLAGS) -o $@ $^

clean: cleanRom cleanBuild

cleanRom:
	@rm -rf $(PROJECT_NAME).*

cleanBuild:
	@rm -rf $(OBJDIR)
	