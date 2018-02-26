# Makefile

EXEC := tAItris

SRC_DIR := ./src
RES_DIR := ./res
DATA_DIR := ./data
BUILD_DIR := ./build
BIN_DIR := ./bin

SRC := $(shell find $(SRC_DIR) -name *.c)
OBJ := $(subst $(SRC_DIR),$(BUILD_DIR),$(SRC:.c=.o))
DEP := ${OBJ:.o=.d}

MKDIR_P ?= mkdir -p
FIND ?= find
RSYNC ?= rsync

CC := gcc
CPPFLAGS := -MMD
CFLAGS := -Wall -Wextra -std=c99 -O0 -g3
LDFLAGS :=
LDLIBS :=

all: $(BIN_DIR) ## Make the project

$(BIN_DIR): $(BIN_DIR)/$(EXEC) $(BIN_DIR)/$(RES_DIR) $(BIN_DIR)/$(DATA_DIR)

$(BIN_DIR)/$(EXEC): $(OBJ)
	@echo "Building executable $(OK_COLOR)$@$(NO_COLOR)"
	@$(MKDIR_P) $(dir $@)
	$(CC) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)
	@echo ""

$(BIN_DIR)/$(RES_DIR):
	@echo "Syncing $(COM_COLOR)$(RES_DIR)$(NO_COLOR) to $(COM_COLOR)$(BIN_DIR)$(NO_COLOR)"
	@$(RSYNC) -rup --delete $(RES_DIR) $(BIN_DIR)

$(BIN_DIR)/$(DATA_DIR):
	@echo "Syncing $(COM_COLOR)$(DATA_DIR)$(NO_COLOR) to $(COM_COLOR)$(BIN_DIR)$(NO_COLOR)"
	@$(RSYNC) -rup --delete $(DATA_DIR) $(BIN_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $(OBJ_COLOR)$<$(NO_COLOR)"
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@echo ""

resources: $(BIN_DIR)/$(RES_DIR) $(BIN_DIR)/$(DATA_DIR) ## Make resources

save: ## Save data from bin
	@echo "Saving data from $(COM_COLOR)$(BIN_DIR)$(NO_COLOR) to $(COM_COLOR)$(DATA_DIR)$(NO_COLOR)"
	@$(RSYNC) -rup --delete $(BIN_DIR)/$(DATA_DIR) ./

clean: ## Clean the project
	@echo "Cleaning $(COM_COLOR)$(BUILD_DIR)$(NO_COLOR) and $(COM_COLOR)$(BIN_DIR)$(NO_COLOR)"
	@$(FIND) $(BUILD_DIR) -mindepth 1 ! -name .gitignore -delete
	@$(FIND) $(BIN_DIR) -mindepth 1 ! -name .gitignore -delete

run: $(BIN_DIR) ## Run the exec
	$(BIN_DIR)/$(EXEC)

doc: ## Make documentation
	doxygen Doxyfile

help: ## Show help
	@grep -E '(^[a-zA-Z_-]+:.*?##.*$$)|(^##)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-10s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'

.PHONY: clean help resources save run doc $(BIN_DIR)/$(RES_DIR) $(BIN_DIR)/$(DATA_DIR)

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

-include $(DEP)

# END
