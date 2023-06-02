# Pre-compiler and Compiler flags
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb
PRE_FLAGS := -MMD -MP

# Project directory structure
BIN := bin
SRC_PLAYER := src/player
SRC_MEDIATOR := src/mediator
LIB := 
INC :=

MAINFILE_PLAYER := $(SRC_PLAYER)/main.cpp
MAINFILE_MEDIATOR := $(SRC_MEDIATOR)/main.cpp

# Build directories and output
TARGET_PLAYER := $(BIN)/player
TARGET_MEDIATOR := $(BIN)/mediator
BUILD := build

# Library search directories and flags
EXT_LIB :=
LDFLAGS :=
LDPATHS := $(addprefix -L,$(LIB) $(EXT_LIB))

# Include directories
INC_DIRS_PLAYER := $(INC) $(shell find $(SRC_PLAYER) -type d) 
INC_FLAGS_PLAYER := $(addprefix -I,$(INC_DIRS_PLAYER))
INC_DIRS_MEDIATOR := $(INC) $(shell find $(SRC_MEDIATOR) -type d) 
INC_FLAGS_MEDIATOR := $(addprefix -I,$(INC_DIRS_MEDIATOR))

# Construct build output and dependency filenames
SRCS_PLAYER := $(shell find $(SRC_PLAYER) -name *.cpp)
OBJS_PLAYER := $(subst $(SRC_PLAYER)/,$(BUILD)/player/,$(addsuffix .o,$(basename $(SRCS_PLAYER))))
DEPS_PLAYER := $(OBJS_PLAYER:.o=.d)
SRCS_MEDIATOR := $(shell find $(SRC_MEDIATOR) -name *.cpp)
OBJS_MEDIATOR := $(subst $(SRC_MEDIATOR)/,$(BUILD)/mediator/,$(addsuffix .o,$(basename $(SRCS_MEDIATOR))))
DEPS_MEDIATOR := $(OBJS_MEDIATOR:.o=.d)

# Main task
all: player mediator

player: $(TARGET_PLAYER)

mediator: $(TARGET_MEDIATOR)

# Tasks producing targets from built files
$(TARGET_PLAYER): $(OBJS_PLAYER)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS_PLAYER) -o $@ $(LDPATHS) $(LDFLAGS)

$(TARGET_MEDIATOR): $(OBJS_MEDIATOR)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS_MEDIATOR) -o $@ $(LDPATHS) $(LDFLAGS)

# Compile all player cpp files
$(BUILD)/player/%.o: $(SRC_PLAYER)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(PRE_FLAGS) $(INC_FLAGS_PLAYER) -c -o $@ $< $(LDPATHS) $(LDFLAGS)

# Compile all mediator cpp files
$(BUILD)/mediator/%.o: $(SRC_MEDIATOR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(PRE_FLAGS) $(INC_FLAGS_MEDIATOR) -c -o $@ $< $(LDPATHS) $(LDFLAGS)

# Clean task
.PHONY: clean
clean:
	@rm -rf $(BUILD)/mediator
	@rm -rf $(BUILD)/player
	@rm -rf $(BIN)/mediator
	@rm -rf $(BIN)/player

# Include all dependencies
-include $(DEPS)