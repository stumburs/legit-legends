CC = g++
CFLAGS = -std=c++20 -g -Wall -I./include -O3
LDFLAGS = -L./lib -lraylib
SRCS = $(wildcard src/*.cpp)
OUT_NAME = legit-legends

build: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(OUT_NAME)

run: build
	./$(OUT_NAME)

.PHONY: build clean run

clean:
	rm -rf $(OUT_NAME)