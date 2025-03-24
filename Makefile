CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -g -Ofast -std=c11
CXXFLAGS = -Wall -Wextra -g -Ofast -std=c++17

CSRC = src/main.c src/utils.c src/obfuscator.c
CXXSRC = src/utils.cpp

INCLUDE = -Iinclude

OUTPUT = build/sinister

LIBS = -lelf

COBJS = $(CSRC:%.c=build/c/%.o)
CXXOBJS = $(CXXSRC:%.cpp=build/cpp/%.o)

all: build_dir $(OUTPUT)

build_dir:
	mkdir -p build
	mkdir -p build/cpp/src
	mkdir -p build/c/src

build/c/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

build/cpp/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OUTPUT): $(COBJS) $(CXXOBJS)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(COBJS) $(CXXOBJS) -o $(OUTPUT) $(LIBS)

clean:
	rm -f $(COBJS) $(CXXOBJS)

.PHONY: all clean