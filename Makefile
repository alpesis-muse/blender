# ----------------------------------------------------------------------------

BUILD_DIR = _build
PROJECT_DIR = blender
TESTS_DIR = tests

# ----------------------------------------------------------------------------

CC = g++
CC_OPTS = -std=c++11

# ----------------------------------------------------------------------------

all: test

test:
	$(CC) -o $(BUILD_DIR)/test_multiband_blender $(TESTS_DIR)/test_multiband_blender.cc
	$(BUILD_DIR)/test_multiband_blender
