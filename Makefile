# Makefile

CC = gcc
CFLAGS = -Wall -Iinclude -fsanitize=address -O0
LDFLAGS = -fsanitize=address

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = bin

# List your source files and test programs
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%,$(TEST_FILES))

# Default target to build all test programs
all: $(TEST_EXECUTABLES)

# Rule to build test executables
$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(SRC_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Run all test programs
run_tests: $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES); do \
		echo "Running $$test"; \
		ASAN_OPTIONS=detect_leaks=1 ./$$test; \
	done

# Clean rule
clean:
	@rm -rf $(BUILD_DIR)

# PHONY targets to avoid conflicts with files of the same name
.PHONY: all run_tests clean
