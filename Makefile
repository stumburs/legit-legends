CC = g++
CFLAGS = -std=c++20 -g -Wall -I./include -O3
LDFLAGS = -L./lib -lraylib
SRCS = $(wildcard src/*.cpp)

# Detect OS
ifeq ($(OS), Windows_NT)
	DETECTED_OS := Windows
	TARGET := legit-legends.exe
else
	DETECTED_OS := $(shell uname)
	TARGET := legit-legends
endif

# Add additional linking flags for Windows
ifeq ($(DETECTED_OS), Windows)
    LDFLAGS += -lwinmm -lgdi32
endif

# Build executable
build: $(SRCS)
	$(info Building for: $(DETECTED_OS))
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

# Build and run executable
run: build
	./$(TARGET)

# Delete executable
clean:
ifeq ($(DETECTED_OS), Windows)
	del $(TARGET)
endif
ifeq ($(DETECTED_OS), Linux)
	rm -rf $(TARGET)
endif