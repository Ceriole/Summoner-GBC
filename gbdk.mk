.PHONY: all rom clean cleanRom cleanBuild cleanRes

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

SRC				= $(call rwildcard, $(SRCDIR), *.c) $(call rwildcard, $(RESDIR), *.c)
ASM				= $(call rwildcard, $(SRCDIR), *.s)
OBJ				= $(addprefix $(OBJDIR)/, $(SRC:.c=.o) $(ASM:.s=.o))

DEBUGFLAG		?= -debug
INCDIRS			+= . $(SRCDIR)
INCFLAGS		= $(addprefix -I, $(INCDIRS))
CFLAGS			= $(INCFLAGS) -Wf-MMD $(DEBUGFLAG)
LCCFLAGS		= -msm83:gb -Wm-yt0x1B -Wl-j -Wm-yC -Wm-yoA -Wm-ya4 -Wb-ext=.rel -Wb-v -Wm-Z -Wm-yn"$(PROJECT_NAME)" -Wm-yj -autobank

EXT				:= gbc

ROMFILE			= $(subst $() $(),_,$(PROJECT_NAME)).$(EXT)

Q ?= @

all: $(ROMFILE)

DEPS = $(OBJ:%.o=%.d)

-include $(DEPS)

$(OBJDIR)/%.o: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/%.o: %.s
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(CFLAGS) -c -o $@ $< 

$(RESDIR)/%.h:
	@echo Making resource $@
	$(MAKE) -C $(RESDIR) $(patsubst $(RESDIR)/%, %, $@)

# If needed, compile .c into .s assembly files.
# Not normally required if .c is directly compiled into .o files.
$(OBJDIR)/%.s: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)$(LCC) $(CFLAGS) -S -o $@ $<

$(PROJECT_NAME).$(EXT): $(LIBS) $(OBJ)
	@echo Making rom $@
	$(Q)$(LCC) $(LCCFLAGS) $(CFLAGS) -o $@ $^

clean: cleanRom cleanBuild

cleanAll: clean cleanRes

cleanRom:
	@rm -rf $(PROJECT_NAME).*

cleanBuild:
	@rm -rf $(OBJDIR)

cleanRes:
	$(MAKE) -C $(RESDIR) clean