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

SRCDIR = src
RESDIR = res
ROOT_DIR = ..
LIB_DIR = lib
BUILD_RUN_BAT = build_run.bat
OUTPUT_DIR = output
OBJ_DIR = $(OUTPUT_DIR)/obj
ROM_DIR = $(OUTPUT_DIR)/rom
ROM_FILE = $(PROJECTNAME).gb
ROM = $(ROM_DIR)/$(ROM_FILE)
CSOURCES = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS = $(CSOURCES:%.c=$(OBJ_DIR)/%.o) $(ASMSOURCES:%.s=$(OBJ_DIR)/%.o)
EMULATOR = $(ROOT_DIR)/$(LIB_DIR)/bgbw64/bgb64.exe
PACKAGE_DIR = package
PACKAGE_ROM = $(PACKAGE_DIR)/$(ROM_FILE)
PACKAGE_LAUNCHER_SRC = $(PACKAGE_DIR)\\Launcher.cs # Win形式パス
PACKAGE_EXE = $(PACKAGE_DIR)/$(PROJECTNAME).exe
PACKAGE_EXE_ICON = $(PACKAGE_DIR)/icon.ico
CSC = C:/Windows/Microsoft.NET/Framework64/v4.0.30319/csc.exe


all: build run

build: $(ROM) 

run: $(ROM)
	$(EMULATOR) $(ROM)

$(BUILD_RUN_BAT): clean
	@echo "REM Automatically generated from Makefile" > $(BUILD_RUN_BAT)
	@make -sn | sed 's|/|\\\\|g' | sed 's|mkdir -p|mkdir|g' | grep -v make >> $(BUILD_RUN_BAT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(ROM_DIR):
	mkdir -p $(ROM_DIR)

# Compile .c files in "src/" to .o object files
$(OBJ_DIR)/%.o: $(SRCDIR)/%.c | $(OBJ_DIR)
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJ_DIR)/%.o: $(RESDIR)/%.c | $(OBJ_DIR)
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJ_DIR)/%.o: $(SRCDIR)/%.s | $(OBJ_DIR)
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJ_DIR)/%.s: $(SRCDIR)/%.c | $(OBJ_DIR)
	$(LCC) $(LCCFLAGS) -S -o $@ $<

# Link the compiled object files into a .gb ROM file
$(ROM): $(OBJS) | $(ROM_DIR)
	$(LCC) $(LCCFLAGS) -o $(ROM) $(OBJS)

clean:
	rm -rf $(OUTPUT_DIR)

# パッケージ関連ターゲット
package: $(PACKAGE_EXE)

$(PACKAGE_EXE): $(PACKAGE_ROM) $(PACKAGE_LAUNCHER_SRC)
	$(CSC) /target:winexe \
		/out:$(PACKAGE_EXE) \
		/win32icon:$(PACKAGE_EXE_ICON) \
		/reference:System.Windows.Forms.dll \
		$(PACKAGE_LAUNCHER_SRC)

$(PACKAGE_ROM): $(ROM)
	cp $(ROM) $(PACKAGE_DIR)/$(ROM_FILE)