CXX = g++

CXXFLAGS = -Wall -Wextra -g -Ofast -std=c++17
CXXSRC = src/main.cpp src/obfuscator.cpp src/utils.cpp src/elf_utils.cpp

INCLUDE = -Iinclude
OUTPUT = build/sinister

LIBS = -lelf

BUILD_DIR = build
SRC_DIR = src

OBJS = $(CXXSRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(OUTPUT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	rm -f $(OBJS) $(OUTPUT)

.PHONY: all clean
