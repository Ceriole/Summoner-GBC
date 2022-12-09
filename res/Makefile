.PHONY: clean

include ../cfg.mk

rwildcard	=	$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

OUTDIR		:= gen

# Aseprite executeable
ASE			:= $(ASEPRITE_HOME)/Aseprite.exe -b
# RGBDS graphics converter
PNG2ASSET	:= $(GBDK_HOME)/bin/png2asset

OPTFILES	:= $(patsubst ./%, %, $(call rwildcard,.,*.opt))
ASEFILES	:= $(patsubst ./%, %, $(call rwildcard,.,*.ase))
ASEPNGFILES	:= $(addprefix $(OUTDIR)/, $(ASEFILES:.ase=.png))
PNGFILES	:= $(filter-out $(ASEPNGFILES), $(patsubst ./%, %, $(call rwildcard,.,*.png)))

# See https://www.aseprite.org/docs/cli for Aseprite options. (.aseopt file)

$(OUTDIR)/%.png: %.ase
	@echo Exporting $< to $@ 
	@mkdir -p $(dir $@)
	$(Q)$(ASE) $< --sheet $@

# See https://gbdk-2020.github.io/gbdk-2020/docs/api/docs_toolchain_settings.html#autotoc_md238 for png2asset options.

$(OUTDIR)/%.h: %.png
	@echo Converting $< to $@
	@mkdir -p $(dir $@)
	$(Q)$(PNG2ASSET) $< $(shell cat $(<:.png=.opt))

$(OUTDIR)/%.h: $(OUTDIR)/%.png
	@echo Converting $< to $@
	@mkdir -p $(dir $@)
	$(Q)$(PNG2ASSET) $< $(shell cat $(<:$(OUTDIR)/%.png=%.opt))

clean:
	@rm -rf $(OUTDIR)

.SECONDARY: