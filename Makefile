# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -g -Wall -I./include -O3

# Linker flags
LDFLAGS := -L./lib -lraylib

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Target executable
TARGET := $(BIN_DIR)/legit-legends

# Detect OS
ifeq ($(OS), Windows_NT)
	DETECTED_OS := Windows
else
	DETECTED_OS := $(shell uname)
endif

# Add additional linking flags for Windows
ifeq ($(DETECTED_OS), Windows)
    LDFLAGS += -lwinmm -lgdi32
endif

# Default rule
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR) $(OBJ_DIR):
	mkdir $@

PHONY: clean run

# Delete executable
clean:
ifeq ($(DETECTED_OS), Windows)
	del $(OBJ_DIR) $(BIN_DIR)
endif
ifeq ($(DETECTED_OS), Linux)
	rm -rf $(OBJ_DIR) $(BIN_DIR)
endif

# Build and run executable
run: $(TARGET)
	./$(TARGET)
