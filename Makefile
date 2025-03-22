CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = src/main.c src/utils.c
INCLUDE = -Iinclude

OUTPUT = build/sinister

all: build_dir $(OUTPUT)

build_dir:
	mkdir -p build

$(OUTPUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
	rm -f build/*.o

.PHONY: all clean test