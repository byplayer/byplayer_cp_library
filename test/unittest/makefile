# Requires the following project directory structure:
#  /src
#
# Following directories are generated
#  /out
#    /release
#      /bin
#      /obj
#    /debug
#      /bin
#      /obj

PROGRAM_NAME := $(shell basename `readlink -f .`)

# compiler
CXX := clang++
CXXFLAGS := -std=c++2b \
			-Weverything -Wall -Wextra -Wpointer-arith -Wcast-qual \
			-Wno-missing-braces -Wempty-body \
			-Wno-error=deprecated-declarations \
			-Wno-c++98-compat \
			-Wno-c++98-compat-pedantic \
			-Wno-poison-system-directories \
			-pedantic-errors -pedantic \
			-mtune=native \
			-march=native \
			-fconstexpr-depth=2147483647 \
			-fconstexpr-steps=214748364
LIBS = -L/opt/homebrew/opt/llvm/lib
LIBS += -L./gtest/lib -lgtest -lgmock -lgtest_main

TLE := 4

# out
OUT_BASE := out
RELEASE_OUT_DIR := $(OUT_BASE)/release
DEBUG_OUT_DIR := $(OUT_BASE)/debug

ifeq ($(DEBUG),1)
OUT_DIR := $(DEBUG_OUT_DIR)
CXXFLAGS += -g -D _DEBUG=1
else
OUT_DIR := $(RELEASE_OUT_DIR)
CXXFLAGS += -O2 -D NDEBUG
endif

SOURCE_DIR := src
SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)

# program
PROGRAM_DIR := $(OUT_DIR)/bin
PROGRAM := $(PROGRAM_DIR)/$(PROGRAM_NAME)

SOURCE_NAMES = $(notdir $(SOURCES))

# headers
HEADER_DIR := include
HEADERS := $(wildcard $(HEADER_DIR)/*.h)

INCLUDES += -I/opt/homebrew/opt/llvm/include
INCLUDES += -I../ac-library
INCLUDES += -I../../include
INCLUDES += -I./gtest/include


# objs
OBJ_DIR := $(OUT_DIR)/obj
OBJS := $(addprefix $(OBJ_DIR)/,$(SOURCE_NAMES:.cpp=.o))

.PHONY: all
all: $(PROGRAM)
$(PROGRAM): $(OBJS)
	@mkdir -p $(PROGRAM_DIR)
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $(PROGRAM)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) $(INCLUDES) -c $^ -o $@

.PHONY : clean
clean:
	$(RM) -r $(OUT_BASE)

.PHONY : run
run: $(PROGRAM)
	$(PROGRAM)

.PHONY : test
test: $(PROGRAM)
	$(PROGRAM)

.DEFAULT_GOAL := test
