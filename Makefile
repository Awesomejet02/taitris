TARGET_EXEC:=tAItris

BIN_DIR:=./bin
BUILD_DIR:=./build
SRC_DIRS:=./src

SRCS:=$(shell find $(SRC_DIRS) -name *.c -or -name *.s)
OBJS:=$(SRCS:%=$(BUILD_DIR)/%.o)
DEPS:=$(OBJS:.o=.d)

CC=gcc
CPPFLAGS= -MMD `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -std=c99 -fgnu89-inline -O0 -g3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -export-dynamic -lSDL_ttf -lSDL_image -lm

all: $(BIN_DIR)/$(TARGET_EXEC)

$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# C source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDLIBS)

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/$(TARGET_EXEC)
	find $(BUILD_DIR) -mindepth 1 ! -name .gitignore -delete

-include $(DEPS)

MKDIR_P ?= mkdir -p
