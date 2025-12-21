#
# A Makefile that compiles all .c and .s files in "src" and "res" 
# subdirectories and places the output in a "obj" subdirectory
#

# ビルドターゲット
TARGET ?= release

# 実行環境の判別
ifeq ($(OS), Windows_NT)
    OS_TYPE := win
else
    ifeq ($(shell uname -s), Darwin)
        OS_TYPE := mac
    endif
endif
ifndef OS_TYPE
    $(error 非対応のOS($(shell uname -s))です)
endif

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
ifndef GBDK_HOME
	GBDK_HOME = $(ROOT_DIR)/$(LIB_DIR)/gbdk/
endif

LCC = $(GBDK_HOME)bin/lcc

# You can set the name of the .gb ROM file here
PROJECTNAME = gb1

SRCDIR = src
RESDIR = res
ROOT_DIR = ..
LIB_DIR = lib/$(OS_TYPE)
OUTPUT_ROOT_DIR = output
OUTPUT_DIR = $(OUTPUT_ROOT_DIR)/$(OS_TYPE)/$(TARGET)
OBJ_DIR = $(OUTPUT_DIR)/obj
ROM_DIR = $(OUTPUT_DIR)/rom
ROM_FILE = $(PROJECTNAME).gb
ROM = $(ROM_DIR)/$(ROM_FILE)
CSOURCES = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS = $(CSOURCES:%.c=$(OBJ_DIR)/%.o) $(ASMSOURCES:%.s=$(OBJ_DIR)/%.o)
BGB_BIN = $(ROOT_DIR)/$(LIB_DIR)/bgbw64/bgb64.exe
SAMEBOY_HOME = $(ROOT_DIR)/$(LIB_DIR)/sameboy
SAMEBOY_ARG =
SAMEBOY_SHADER_FILES := $(wildcard $(SAMEBOY_HOME)/Shaders/*.fsh) $(wildcard $(SAMEBOY_HOME)/Shaders/*.vsh)
CSC = C:/Windows/Microsoft.NET/Framework64/v4.0.30319/csc.exe
PACKAGE_DIR = package/$(OS_TYPE)
PACKAGE_INTERMEDIATE_DIR = $(OUTPUT_DIR)/package_intermediate
PACKAGE_LAUNCHER_SRC = $(PACKAGE_DIR)/Launcher.cs
PACKAGE_CONFIG_SRC = $(PACKAGE_INTERMEDIATE_DIR)/Config.cs
PACKAGE_SRCS = $(PACKAGE_LAUNCHER_SRC) $(PACKAGE_CONFIG_SRC)
PACKAGE_EXE = $(OUTPUT_DIR)/$(PROJECTNAME).exe
PACKAGE_EXE_ICON = $(PACKAGE_DIR)/icon.ico
PACKAGE_BASE_RESOURCES = \
	/resource:$(SAMEBOY_BIN),sameboy.exe \
	/resource:$(SAMEBOY_HOME)/SDL2.dll,SDL2.dll \
	/resource:$(SAMEBOY_HOME)/xaudio2_9redist.dll,xaudio2_9redist.dll \
	/resource:$(SAMEBOY_HOME)/cgb_boot.bin,cgb_boot.bin \
	/resource:$(SAMEBOY_HOME)/dmg_boot.bin,dmg_boot.bin \
	/resource:$(ROM),$(ROM_FILE)
PACKAGE_SHADER_RESOURCES = $(foreach f,$(SAMEBOY_SHADER_FILES),/resource:$f,Shaders__$(notdir $f))
PACKAGE_RESOURCES = $(PACKAGE_BASE_RESOURCES) $(PACKAGE_SHADER_RESOURCES)

# OSごとに大きく違う定義
ifeq ($(OS_TYPE), win)
    SAMEBOY_BIN = $(SAMEBOY_HOME)/sameboy.exe
else
    ifeq ($(OS_TYPE), mac)
        SAMEBOY_BIN = $(SAMEBOY_HOME)/SameBoy.app/Contents/MacOS/SameBoy
	endif
endif

# コンパイル追加設定
## GB/GBColor両対応
LCCFLAGS += -Wm-yc
## resディレクトリをヘッダインクルードパスとして追加
LCCFLAGS += -Ires

# ビルドターゲットごとの設定
EMULATOR_BIN = $(SAMEBOY_BIN)
ifeq ($(TARGET), debug)
	LCCFLAGS += -debug -v -Wf-DDEBUG
	ifeq ($(OS_TYPE), win)
		EMULATOR_BIN = $(BGB_BIN)
	endif
endif

# 以降はmakeターゲットに関する実装のみ
all: build run

build: $(ROM) 

run: $(ROM)
	$(EMULATOR_BIN) $(ROM)

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

clean_all:
	rm -rf $(OUTPUT_ROOT_DIR)

# パッケージ関連ターゲット(win環境でのみ有効)
ifeq ($(OS_TYPE), win)

package: $(PACKAGE_EXE)

$(PACKAGE_EXE): $(ROM) $(PACKAGE_SRCS)
	$(CSC) /target:winexe \
		/out:$(PACKAGE_EXE) \
		/win32icon:$(PACKAGE_EXE_ICON) \
		/reference:System.Windows.Forms.dll \
		$(PACKAGE_RESOURCES) \
		$(subst /,\,$(PACKAGE_SRCS))

$(PACKAGE_CONFIG_SRC): Makefile | $(PACKAGE_INTERMEDIATE_DIR)
	@echo // Automatically generated from Makefile > $(PACKAGE_CONFIG_SRC)
	@echo class Config { >> $(PACKAGE_CONFIG_SRC)
	@echo '    public const string AppName = "$(PROJECTNAME)";' >> $(PACKAGE_CONFIG_SRC)
	@echo '    public const string SameboyArg = "$(SAMEBOY_ARG)";' >> $(PACKAGE_CONFIG_SRC)
	@echo } >> $(PACKAGE_CONFIG_SRC)

$(PACKAGE_INTERMEDIATE_DIR):
	mkdir -p $(PACKAGE_INTERMEDIATE_DIR)

endif