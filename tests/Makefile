OS := $(shell uname)
ifeq ($(OS), Darwin)
    SO_EXT := dylib
else
    SO_EXT := so
endif

.PHONY = all clean test runtest

PROGRAM = ac_test
all: runtest

CXXFLAGS = -O3 -g -march=native -Wall -DDEBUG
MYCXXFLAGS = -MMD -I.. $(CXXFLAGS)
%.o : %.cxx
	$(CXX) $< -c $(MYCXXFLAGS)

-include dep.cxx
SRC = test_main.cxx ac_test_simple.cxx

OBJ = ${SRC:.cxx=.o}

-include test_dep.txt
-include bench_dep.txt

$(PROGRAM) : $(OBJ) ../libac.$(SO_EXT)
	$(CXX) $(OBJ) -L.. -lac -o $@
	-cat *.d > test_dep.txt

ifneq ($(OS), Darwin)
runtest:$(PROGRAM)
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):.. ./$(PROGRAM) testinput/*
else
runtest:$(PROGRAM)
	DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH):.. ./$(PROGRAM) testinput/*
endif

clean:
	-rm -f *.o *.d dep.txt $(PROGRAM) $(BENCHMARK)
