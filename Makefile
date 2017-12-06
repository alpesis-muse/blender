# ----------------------------------------------------------------------------

BUILD_DIR = _build
PROJECT_DIR = blender
TESTS_DIR = tests

HEADERS = -I$(PROJECT_DIR)/*.hh \
          -I$(PROJECT_DIR)/utils/*.h \
          -I$(PROJECT_DIR)/utils/*.hh \
          -I$(PROJECT_DIR)/feature/*.hh \
          -I$(PROJECT_DIR)/blender/*.hh


SOURCES = $(PROJECT_DIR)/utils/*.cc \
          $(PROJECT_DIR)/feature/*.cc \
          $(PROJECT_DIR)/blender/*.cc

# ----------------------------------------------------------------------------

EIGEN_INCLUDE_DIR = /usr/include/eigen3/

# ----------------------------------------------------------------------------

CC = g++
CC_OPTS = -std=c++11
CC_OPTS_INCLUDES = -I$(EIGEN_INCLUDE_DIR)
CC_FLAGS = $(CC_OPTS) $(CC_OPTS_INCLUDES)
CC_LDFLAGS = 

# ----------------------------------------------------------------------------

PROJECT_SOURCES := $(wildcard $(PROJECT_DIR)/*.c)
PROJECT_OBJECTS := $(patsubst %, $(BUILD_DIR)/%, $(notdir $(PROJECT_SOURCES:.c=.o)))

$(BUILD_DIR)/%.o : $(PROJECT_DIR)/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@ $(CC_LDFLAGS)


# ----------------------------------------------------------------------------

all: test

test:
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/test_multiband_blender $(TESTS_DIR)/test_multiband_blender.cc $(SOURCES) $(HEADERS) $(CC_LDFLAGS) 
	$(BUILD_DIR)/test_multiband_blender
