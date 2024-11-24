OS := $(shell uname)

ifeq ($(OS), Darwin)
    SO_EXT := dylib
else
    SO_EXT := so
endif

#############################################################################
#
#           Binaries we are going to build
#
#############################################################################
#
C_SO_NAME = libac.$(SO_EXT)
AR_NAME = libac.a

#############################################################################
#
#           Compile and link flags
#
#############################################################################

# Available directives:
# -DDEBUG : Turn on debugging support
# -DVERIFY : To verify if the slow-version and fast-version implementations
#            get exactly the same result. Note -DVERIFY implies -DDEBUG.
#
COMMON_FLAGS = -O3 #-g -DVERIFY -msse2 -msse3 -msse4.1
COMMON_FLAGS += -fvisibility=hidden -Wall $(CXXFLAGS) $(MY_CXXFLAGS) $(CPPFLAGS)

SO_CXXFLAGS = $(COMMON_FLAGS) -fPIC
SO_LFLAGS = $(COMMON_FLAGS) $(LDFLAGS)
AR_CXXFLAGS = $(COMMON_FLAGS)

# -DVERIFY implies -DDEBUG
ifneq ($(findstring -DVERIFY, $(COMMON_FLAGS)), )
ifeq ($(findstring -DDEBUG, $(COMMON_FLAGS)), )
    COMMON_FLAGS += -DDEBUG
endif
endif

AR = ar
AR_FLAGS = cru

#############################################################################
#
#       Divide source codes and objects into several categories
#
#############################################################################
#
SRC_COMMON := ac_fast.cxx ac_slow.cxx
LIBAC_SO_SRC := $(SRC_COMMON) ac.cxx    # source for libac.so
LIBAC_A_SRC := $(LIBAC_SO_SRC)          # source for libac.a

#############################################################################
#
#                   Make rules
#
#############################################################################
#
.PHONY = all clean test benchmark prepare
all : $(C_SO_NAME)

-include c_so_dep.txt
-include ar_dep.txt

BUILD_SO_DIR := build_so
BUILD_AR_DIR := build_ar

$(BUILD_SO_DIR) :; mkdir $@
$(BUILD_AR_DIR) :; mkdir $@

$(BUILD_SO_DIR)/%.o : %.cxx | $(BUILD_SO_DIR)
	$(CXX) $< -c $(SO_CXXFLAGS) -MMD -o $@

$(BUILD_AR_DIR)/%.o : %.cxx | $(BUILD_AR_DIR)
	$(CXX) $< -c $(AR_CXXFLAGS) -MMD -o $@

ifneq ($(OS), Darwin)
$(C_SO_NAME) : $(addprefix $(BUILD_SO_DIR)/, ${LIBAC_SO_SRC:.cxx=.o})
	$(CXX) $+ -shared -Wl,-soname=$(C_SO_NAME) $(SO_LFLAGS) -o $@
	cat $(addprefix $(BUILD_SO_DIR)/, ${LIBAC_SO_SRC:.cxx=.d}) > c_so_dep.txt
else
$(C_SO_NAME) : $(addprefix $(BUILD_SO_DIR)/, ${LIBAC_SO_SRC:.cxx=.o})
	$(CXX) $+ -shared $(SO_LFLAGS) -o $@
	cat $(addprefix $(BUILD_SO_DIR)/, ${LIBAC_SO_SRC:.cxx=.d}) > c_so_dep.txt
endif

#############################################################################
#
#           Misc
#
#############################################################################
#
test : $(C_SO_NAME)
	$(MAKE) -C tests

benchmark: $(C_SO_NAME)
	$(MAKE) benchmark -C tests

clean :
	-rm -rf *.o *.d c_so_dep.txt ar_dep.txt $(TEST) \
        $(C_SO_NAME) $(TEST) $(BUILD_SO_DIR) $(BUILD_AR_DIR)
	make clean -C tests
