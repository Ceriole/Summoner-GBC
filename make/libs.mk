.PHONY: clean cleanHUGE

ifndef LIBDIR
$(error LIBDIR is not set. Example "libs")
endif
ifndef OBJDIR
$(error OBJDIR is not set. Example "build")
endif
ifndef TOOLSDIR
$(error TOOLSDIR is not set. Example "tools")
endif
ifndef RGBDS_51_HOME
$(error RGBDS_51_HOME is not set. Example "C:/RGBDS51")
endif

HUGEDIR			?= $(LIBDIR)/hUGEDriver

HUGETOOLS		:= $(HUGEDIR)/tools
RGBASM			:= $(RGBDS_51_HOME)/rgbasm
RGB2SDAS		:= $(TOOLSDIR)/rgb2sdas.exe

HUGEASMFLAGS	:= -DGBDK -i$(HUGEDIR)
HUGECONVFLAGS	:= -b0

Q ?= @

$(RGB2SDAS):
	@$(MAKE) -C $(HUGEDIR)/tools
	@mkdir -p $(dir $@)
	@mv $(HUGEDIR)/tools/$(notdir $@) $(RGB2SDAS)

$(OBJDIR)/$(HUGEDIR)/hUGEDriver.obj.o: $(OBJDIR)/$(HUGEDIR)/hUGEDriver.obj $(RGB2SDAS)
	@echo Converting hUGEDriver
	@mkdir -p $(dir $@)
	$(Q)$(RGB2SDAS) $(HUGECONVFLAGS) $<
	@echo Updating hUGE object file
# rgb2sdas makes a incompatible file, just due to the O flag. The below command replaces '-mgbz80' (SDCC < 4.1.0) with '-msm83' (SDCC >= 4.2.0)
	$(Q)sed -i 's/-mgbz80/-msm83/' $@

$(OBJDIR)/$(HUGEDIR)/hUGEDriver.obj: $(HUGEDIR)/hUGEDriver.asm
	@echo Compiling hUGEDriver
	@mkdir -p $(dir $@)
	$(Q)$(RGBASM) $(HUGEASMFLAGS) $< -o $@

clean: cleanHUGE

cleanHUGE:
	@rm -rf $(OBJDIR)/$(HUGEDIR)

cleanRgb2Sdas:
	@rm -rf $(RGB2SDAS) $(HUGEDIR)/tools/$(notdir $@)