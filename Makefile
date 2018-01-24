TARGET_EXEC:=tAItris

BIN_DIR:=./bin
BUILD_DIR:=./build
SRC_DIRS:=./src

SRCS:=$(shell find $(SRC_DIRS) -name *.c -or -name *.s)
OBJS:=$(SRCS:%=$(BUILD_DIR)/%.o)
DEPS:=$(OBJS:.o=.d)

CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -O0 -g3
LDFLAGS=
LDLIBS=

all: $(BIN_DIR)/$(TARGET_EXEC)

$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# C source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/$(TARGET_EXEC)
	find $(BUILD_DIR) -mindepth 1 ! -name .gitignore -delete

-include $(DEPS)

MKDIR_P ?= mkdir -p