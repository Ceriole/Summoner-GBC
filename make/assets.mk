
ifndef RESDIR
$(error RESDIR is not set. Example "res")
endif
ifndef OBJDIR
$(error OBJDIR is not set. Example "build")
endif
ifndef ASEPRITE_HOME
$(error RGBDS_HOME is not set. Example "'C:/Program Files (x86)/Steam/steamapps/common/Aseprite'")
endif
ifndef RGBDS_HOME
$(error RGBDS_HOME is not set. Example "D:/RGBDS")
endif


# Aseprite executeable
ASE			:= $(ASEPRITE_HOME)/Aseprite.exe -b
# RGBDS graphics converter
GFXCONV		:= $(RGBDS_HOME)/rgbgfx

# Optfile dumper
OPTFILE		= $(patsubst $(OBJDIR)/%, %, $<.opt)
FILEOPTS	= $(shell cat $(OPTFILE))

Q ?= @

# See https://www.aseprite.org/docs/cli for Aseprite options. (.aseopt file)

$(OBJDIR)/$(RESDIR)/%.png: $(RESDIR)/%.ase $(RESDIR)/%.ase.opt
	@echo Converting $<
	$(Q)$(ASE) $< $(FILEOPTS) --save-as $@

# See https://rgbds.gbdev.io/docs/v0.6.0/rgbgfx.1 for RGBGFX options.

# Rules for Aseprite converted files
$(OBJDIR)/$(RESDIR)/%.chr: $(OBJDIR)/$(RESDIR)/%.png
	@echo Creating chr data $@
	$(Q)$(GFXCONV) $< $(FILEOPTS) -o $@

$(OBJDIR)/$(RESDIR)/%.pal: $(OBJDIR)/$(RESDIR)/%.png
	@echo Creating palette data $@
	$(Q)$(GFXCONV) $< $(FILEOPTS) -p $@

$(OBJDIR)/$(RESDIR)/%.map: $(OBJDIR)/$(RESDIR)/%.png
	@echo Creating map data $@
	$(Q)$(GFXCONV) $< $(FILEOPTS) -t $@

$(OBJDIR)/$(RESDIR)/%.attrmap: $(OBJDIR)/$(RESDIR)/%.png
	@echo Creating attribute map data $@
	$(Q)$(GFXCONV) $< $(FILEOPTS) -a $@

# Rules for png files
$(OBJDIR)/$(RESDIR)/%.chr: $(RESDIR)/%.png
	@echo Creating chr data $@
	$(Q)$(GFXCONV) $< $(FILEOPTS) -o $@

$(OBJDIR)/$(RESDIR)/%.pal: $(RESDIR)/%.png
	@echo Creating palette data $@
	$(Q)$(GFXCONV) $< $(FILEOPTS) -p $@

$(OBJDIR)/$(RESDIR)/%.map: $(RESDIR)/%.png
	@echo Creating map data $@
	$(Q)$(GFXCONV) $< $(FILEOPTS) -t $@

$(OBJDIR)/$(RESDIR)/%.attrmap: $(RESDIR)/%.png
	@echo Creating attribute map data $@
	$(Q)$(GFXCONV) $< $(FILEOPTS) -a $@
