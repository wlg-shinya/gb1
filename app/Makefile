#
# A Makefile that compiles all .c and .s files in "src" and "res" 
# subdirectories and places the output in a "obj" subdirectory
#


# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
ifndef GBDK_HOME
	GBDK_HOME = $(ROOT_DIR)/$(LIB_DIR)/gbdk/
endif

LCC = $(GBDK_HOME)bin/lcc 

# GBDK_DEBUG = ON
ifdef GBDK_DEBUG
	LCCFLAGS += -debug -v
endif


# You can set the name of the .gb ROM file here
PROJECTNAME = gb1

ROOT_DIR = ..
LIB_DIR = lib
SRCDIR = src
OBJDIR = obj
RESDIR = res
BINS = $(OBJDIR)/$(PROJECTNAME).gb
CSOURCES = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)
EMULATOR = $(ROOT_DIR)/$(LIB_DIR)/bgbw64/bgb64.exe

all: build run

build: $(BINS) 

run: $(BINS)
	$(EMULATOR) $(BINS)

build_run.bat: Makefile
	@echo "REM Automatically generated from Makefile" > build_run.bat
	@make -sn | sed 's|/|\\\\|g' | sed 's|mkdir -p|mkdir|g' | grep -v make >> build_run.bat

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o: $(RESDIR)/%.c | $(OBJDIR)
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o: $(SRCDIR)/%.s | $(OBJDIR)
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s: $(SRCDIR)/%.c | $(OBJDIR)
	$(LCC) $(LCCFLAGS) -S -o $@ $<

# Link the compiled object files into a .gb ROM file
$(BINS): $(OBJS)
	$(LCC) $(LCCFLAGS) -o $(BINS) $(OBJS)

clean:
	rm -rf $(OBJDIR)
