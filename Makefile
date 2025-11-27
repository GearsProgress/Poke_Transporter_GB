# Build configuration (set to either 'debug' or 'release')
BUILD_TYPE := debug

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/gba_rules

#---------------------------------------------------------------------------------
# the LIBGBA path is defined in gba_rules, but we have to define LIBTONC ourselves
#---------------------------------------------------------------------------------
LIBTONC := $(DEVKITPRO)/libtonc

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# DATA is a list of directories containing binary data
# GRAPHICS is a list of directories containing files to be processed by grit
#
# All directories are specified relative to the project directory where
# the makefile is found
#
#---------------------------------------------------------------------------------
TARGET		:= $(notdir $(CURDIR))_mb
BUILD		:= build
SOURCES		:= source source/pccs
INCLUDES	:= include include/pccs
DATA		:= data
MUSIC		:= audio
GRAPHICS	:= graphics

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-mthumb -mthumb-interwork

CFLAGS	:=	-Wall -O2\
		-mcpu=arm7tdmi -mtune=arm7tdmi -masm-syntax-unified\
		$(ARCH) 

CFLAGS	+=	$(INCLUDE) -ffunction-sections -fdata-sections -Os -Wall -mthumb -mcpu=arm7tdmi -mtune=arm7tdmi -fstack-usage
CXXFLAGS	:=	$(CFLAGS) -g0 -fno-rtti -fno-exceptions -fdata-sections -ffunction-sections -std=c++20 -Wno-volatile -D_GLIBCXX_USE_CXX20_ABI=0 -fstack-usage

ifeq ($(BUILD_TYPE), debug)
	CFLAGS += -g -DDEBUG
	CXXFLAGS += -g -DDEBUG
else ifeq ($(BUILD_TYPE), release)


endif

ASFLAGS	:=	$(ARCH)
LDFLAGS	=	-Os $(ARCH) -Wl,-Map,$(notdir $*.map) -Wl,--gc-sections -mthumb -mcpu=arm7tdmi -mtune=arm7tdmi -Wl,-Map,output.map,--cref -nodefaultlibs

# eliminate libsysbase_libsysbase_a-handle_manager.o and its 4KB IWRAM buffer
LDFLAGS += -Wl,--wrap=__get_handle -Wl,--wrap=_close_r

CFLAGS += -flto
LDFLAGS += -flto

ifeq ($(BUILD_TYPE), debug)
ASFLAGS += -g
LDFLAGS += -g
endif

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= -lmm -ltonc -lgba -lc -lgcc -lsysbase


#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib.
# the LIBGBA path should remain in this list if you want to use maxmod
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(LIBGBA) $(LIBTONC)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------


ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
			$(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
PNGFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.png)))

#ifneq ($(strip $(MUSIC)),)
#	export AUDIOFILES	:=	$(foreach dir,$(notdir $(wildcard $(MUSIC)/*.*)),$(CURDIR)/$(MUSIC)/$(dir))
#	BINFILES += soundbank.bin
#endif

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export OFILES_GRAPHICS := $(PNGFILES:.png=.o)

export OFILES := $(OFILES_SOURCES) $(OFILES_GRAPHICS)

export HFILES := $(addsuffix .h,$(subst .,_,$(BINFILES))) $(PNGFILES:.png=.h)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD) \
					-I$(CURDIR)/tools/data-generator/include

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) generate_data clean

all: $(BUILD)

generate_data:
	mkdir -p data
	mkdir -p to_compress
	@env -i "PATH=$(PATH)" $(MAKE) -C tools/data-generator
	@echo
	@echo "----------------------------------------------------------------"
	@echo
	@tools/data-generator/data-generator to_compress
	@python3 text_helper/main.py
	@echo "Compressing bin files!" 
	@echo -n "["
	@find to_compress -name "*.bin" -print0 | xargs -0 -n1 ./compress_lz10.sh
	@echo "]"
	@echo "Compressing finished!"
	@echo
	@echo "----------------------------------------------------------------"
	@echo

#---------------------------------------------------------------------------------
$(BUILD): generate_data
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	@mkdir -p loader/data
	@cp $(TARGET).gba loader/data/multiboot_rom.bin
	@$(MAKE) -C loader

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@$(MAKE) -C tools/data-generator clean
	@$(MAKE) -C loader clean
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba data/ to_compress/
	@rm -f text_helper/output.json



#---------------------------------------------------------------------------------
else

BINFILES	:=	$(foreach dir,../$(DATA),$(notdir $(wildcard $(dir)/*.*)))
export OFILES_BIN := $(addsuffix .o,$(BINFILES))
OFILES := $(OFILES_BIN) $(OFILES)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

$(OUTPUT).gba	:	$(OUTPUT).elf

$(OUTPUT).elf	:	$(OFILES)

$(OFILES_SOURCES) : $(HFILES)

#---------------------------------------------------------------------------------
# The bin2o rule should be copied and modified
# for each extension used in the data directories
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# rule to build soundbank from music files
#---------------------------------------------------------------------------------
#soundbank.bin soundbank.h : $(AUDIOFILES)
#---------------------------------------------------------------------------------
#	@mmutil $^ -osoundbank.bin -hsoundbank.h

#---------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension
#---------------------------------------------------------------------------------
%.bin.o	%_bin.h :	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
# This rule creates C source files using grit
# grit takes an image file and a .grit describing how the file is to be processed
# add additional rules like this for each image extension
# you use in the graphics folders
#---------------------------------------------------------------------------------
%.c %.h: %.png %.grit
#---------------------------------------------------------------------------------
	@echo "grit $(notdir $<)"
	@grit $< -ftc -o$*

# make likes to delete intermediate files. This prevents it from deleting the
# files generated by grit after building the GBA ROM.
.SECONDARY:

-include $(DEPSDIR)/*.d
#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
