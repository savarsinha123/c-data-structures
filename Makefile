CC = gcc
CFLAGS = -Wall -Iinclude -fsanitize=address -g
LDFLAGS = -fsanitize=address

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = bin

# List your source files and test programs
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%,$(TEST_FILES))

# Default target to build all test programs and run Python script
all: run_tests run_python_script

# Rule to build test executables
$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(SRC_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lm

# Run all test programs
run_tests: $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES); do \
		echo "Running $$test"; \
		ASAN_OPTIONS=detect_leaks=1 ./$$test; \
	done
	@echo "Finished running tests"

# Run Python script
run_python_script:
	@echo "Creating complexity plots in figs/"
	python3 plot_complexity.py
	@echo "Finished creating plots"

# Clean rule
clean:
	@rm -rf $(BUILD_DIR)

# PHONY targets to avoid conflicts with files of the same name
.PHONY: all run_tests run_python_script clean
