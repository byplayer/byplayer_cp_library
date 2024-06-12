# Requires the following project directory structure:
#  /src
#
# Following directories are generated
#  /out
#    /release
#      /bin
#      /depend
#      /obj
#    /debug
#      /bin
#      /depend
#      /obj

PROGRAM_NAME := $(shell basename `readlink -f .`)

# compiler
CXX ?= clang++
CXX_VER ?= c++2b

ifeq ($(CXX),clang++)
CXXFLAGS = -std=$(CXX_VER) \
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
endif

ifeq ($(CXX), g++)
CXXFLAGS = -std=$(CXX_VER) \
			-Wall -Wextra \
			-mtune=native \
			-Wno-missing-braces -Wempty-body \
			-Wno-error=deprecated-declarations \
			-Wno-c++98-compat \
			-Wno-c++98-compat-pedantic \
			-Wno-poison-system-directories \
			-pedantic-errors -pedantic \
			-fconstexpr-depth=2147483647 \
			-fconstexpr-loop-limit=2147483647 \
			-fconstexpr-ops-limit=2147483647
endif

LD = $(CXX)
LDFLAGS = -L./gtest_$(CXX)/lib -lgtest -lgmock -lgtest_main

REPLACE_OBJ_PATH=../../bin/replace_obj_path

# out
OUT_BASE = out/$(CXX)/$(CXX_VER)
RELEASE_OUT_DIR = $(OUT_BASE)/release
DEBUG_OUT_DIR = $(OUT_BASE)/debug

$(OUT_BASE):
	@mkdir -p $(OUT_BASE)

ifeq ($(DEBUG),1)
OUT_DIR = $(DEBUG_OUT_DIR)
CXXFLAGS += -g -D _DEBUG=1
else
OUT_DIR = $(RELEASE_OUT_DIR)
CXXFLAGS += -O2 -D NDEBUG
endif

$(OUT_DIR): $(OUT_BASE)
	@mkdir -p $(OUT_DIR)

SOURCE_DIR := src
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)

# program
PROGRAM_DIR = $(OUT_DIR)/bin
PROGRAM = $(PROGRAM_DIR)/$(PROGRAM_NAME)

SOURCE_NAMES = $(notdir $(SOURCES))

# dependencies
DEPEND_DIR = $(OUT_DIR)/depend
VPATH += $(DEPEND_DIR)
PREDEPENDS = $(addprefix $(DEPEND_DIR)/,$(SOURCE_NAMES:.cpp=.d))
DEPENDS = $(addprefix $(DEPEND_DIR)/,$(SOURCE_NAMES:.cpp=.dep))

$(DEPEND_DIR): $(OUT_DIR)
	@mkdir -p $(DEPEND_DIR)

$(PREDEPENDS): gtest_$(CXX)
$(DEPENDS): $(PREDEPENDS)

# headers
HEADER_DIR = include
HEADERS = $(wildcard $(HEADER_DIR)/*.h)

INCLUDES += -I../../ac-library
INCLUDES += -I../../include
INCLUDES += -I./gtest_$(CXX)/include

# objs
OBJ_DIR = $(OUT_DIR)/obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SOURCE_NAMES:.cpp=.o))

.PHONY: all
all: $(PROGRAM)
$(PROGRAM): $(OBJS) $(DEPENDS)
	@mkdir -p $(PROGRAM_DIR)
	$(LD) $(OBJS) -o $(PROGRAM) $(LDFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp gtest_$(CXX)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) $(INCLUDES) $< -c -o $@

$(DEPEND_DIR)/%.d: $(SOURCE_DIR)/%.cpp $(DEPEND_DIR)
	$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) $(INCLUDES) -MM -MF $@ $<

$(DEPEND_DIR)/%.dep: $(DEPEND_DIR)/%.d $(DEPEND_DIR)
	$(REPLACE_OBJ_PATH) $< $@ $(OBJ_DIR)

googletest/CMakeLists.txt:
	git submodule update --init

gtest_$(CXX): googletest/CMakeLists.txt
	./build_gtest.sh $(CXX)

.PHONY : clean
clean:
	$(RM) -r out

.PHONY : run
run: $(PROGRAM)
	$(PROGRAM)

.PHONY : test
test: $(PROGRAM)
	$(PROGRAM)

.DEFAULT_GOAL = all

IS_DRYRUN = $(findstring n,$(filter-out --%,${MAKEFLAGS}))
ONLY_CLEAN = $(findstring _clean_,_${MAKECMDGOALS}_)

ifeq ($(or ${IS_DRYRUN},${ONLY_CLEAN}),)
	include $(DEPENDS)
endif
