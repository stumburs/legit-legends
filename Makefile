CC = g++
CFLAGS = -std=c++20 -g -Wall -I./include -O3
LDFLAGS = -L./lib -lraylib
SRCS = $(wildcard src/*.cpp)

ifeq ($(OS), Windows_NT)
    DETECTED_OS := Windows
	TARGET := legit-legends.exe
else
    DETECTED_OS := $(shell uname)
	TARGET := legit-legends
endif

build: $(SRCS)
	$(info Building for: $(DETECTED_OS))
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run: build
	./$(TARGET)

clean:
ifeq ($(DETECTED_OS), Windows_NT)
	del $(TARGET)
endif
ifeq ($(DETECTED_OS), Linux)
	rm -rf $(TARGET)
endif

.PHONY: build clean run