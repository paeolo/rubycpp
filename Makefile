.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif

include $(DEVKITARM)/gba_rules

TARGET		:=	output
BUILD		:=	build
EXTENSION   :=  4bpp gbapal gbabg json

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	 :=	-mthumb -mthumb-interwork

CFLAGS	 :=	-g -Wall -O2 \
		-mcpu=arm7tdmi -mtune=arm7tdmi\
 		-fomit-frame-pointer\
		-ffast-math \
		$(ARCH)

CFLAGS	 +=	$(INCLUDE)

CXXFLAGS :=	$(CFLAGS) -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-use-cxa-atexit

ASFLAGS	 :=	-g $(ARCH)
LDFLAGS	  =	-g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS	 :=	-lgba
LIBDIRS	 :=	$(LIBGBA)


ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------
# Sources Files
#---------------------------------------------------------------------------------

SOURCES		       :=	$(shell find src/ -type d)
INCLUDES	       := 	$(shell find include/ -type d)
export DATADIRS    :=   $(shell find data/ -type d) 

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export DEPSDIR	:=	$(CURDIR)/$(BUILD)

VPATH		:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
VPATH       +=  $(foreach dir,$(DATADIRS),$(CURDIR)/$(dir))
export VPATH

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
JSONFILES   :=  $(foreach dir,$(DATADIRS),$(notdir $(wildcard $(dir)/*.json)))
GBFSFILES   :=  $(foreach extension,$(EXTENSION), $(extension).gbfs)

ifeq ($(strip $(CPPFILES)),)
export LD := $(CC)
else
export LD := $(CXX)
endif

export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES := $(GBFSFILES:.gbfs=_gbfs.o) $(OFILES_SOURCES)
export BINFILES :=  $(JSONFILES:.json=.bin)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

#---------------------------------------------------------------------------------
# Project tools
#---------------------------------------------------------------------------------
export PATH	     := $(DEVKITARM)/bin:$(PATH)
export BIN2S 	 := $(CURDIR)/tools/bin2s
export GBFS  	 := $(CURDIR)/tools/gbfs
export JSON2BIN  := $(CURDIR)/tools/json2bin

#---------------------------------------------------------------------------------
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba

#---------------------------------------------------------------------------------
else

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

$(OUTPUT).gba	:	$(OUTPUT).elf
$(OUTPUT).elf	:	$(OFILES)

#---------------------------------------------------------------------------------
# GBFS File
#---------------------------------------------------------------------------------
%.bin: %.json
	$(JSON2BIN) ../config/parser.json $^ $@

%_gbfs.s: %.gbfs
	$(BIN2S) $^ > $@

json.gbfs: $(BINFILES)
	$(GBFS) -n json.gbfs $(BINFILES)

%.gbfs: $(shell find ../data -type d) $(shell find ../data -name "*.$*" -type f)
	$(GBFS) -n $*.gbfs $(shell find ../data -name "*.$*" -type f)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
