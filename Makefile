BINFILE = main
SRC_FOLDER = src
OBJ_FOLDER = obj
DEBUG = true

ifdef VERBOSE
	Q =
	E = @true
else
	Q = @
	E = @echo
endif

C_RESET = \033[00m
C_RED = \033[01;31m
C_DARK_GREEN = \033[00;32m
C_BLUE = \033[00;36m
C_VIOLET = \033[01;35m

OK_STRING=$(C_DARK_GREEN) [OK]$(C_RESET)
ERROR_STRING=$(C_RED) [ERRORS]$(C_RESET)
WARN_STRING=$(C_VIOLET) [WARNINGS]$(C_RESET)

# Source files
CFILES := $(shell find $(SRC_FOLDER) -mindepth 1 -maxdepth 4 -name "*.c")
CXXFILES := $(shell find $(SRC_FOLDER) -mindepth 1 -maxdepth 4 -name "*.cpp")

INFILES := $(CFILES) $(CXXFILES)

# Binary files
OBJFILES := $(CXXFILES:$(SRC_FOLDER)/%.cpp=%) $(CFILES:$(SRC_FOLDER)/%.c=%)
DEPFILES := $(CXXFILES:$(SRC_FOLDER)/%.cpp=%) $(CFILES:$(SRC_FOLDER)/%.c=%)
OFILES := $(OBJFILES:%=$(OBJ_FOLDER)/%.o)

# Compiler
CC = gcc
CXX = g++
LINKER = $(CXX)

# Compiler flags
COMMONFLAGS = -Wall -Wextra -pedantic
LDFLAGS =

ifdef DEBUG
	COMMONFLAGS := $(COMMONFLAGS) -g
endif
CFLAGS = $(COMMONFLAGS) --std=c99
CXXFLAGS = $(COMMONFLAGS) --std=c++11 -DN1AMR -DN1AMR_FILE
LINKERFLAGS = $(CXXFLAGS)
DEPDIR = deps

# Targets
all: $(BINFILE)
ifeq ($(MAKECMDGOALS),)
-include Makefile.dep
endif
ifneq ($(filter-out clean, $(MAKECMDGOALS)),)
-include Makefile.dep
endif

-include Makefile.local

.PHONY: clean all depend
.SUFFIXES:

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	$(E) -n "$(C_BLUE)"C Compiling \"$<\"..."$(C_RESET)"
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CC) -o $@ -c $< $(CFLAGS) 2> temp.log || touch temp.errors
	$(Q)if test -e temp.errors; then echo "$(ERROR_STRING)" && cat temp.log; elif test -s temp.log; then echo "$(WARN_STRING)" && cat temp.log; else echo "$(OK_STRING)"; fi;
	$(Q)if test ! -e temp.errors; then x="1"; else x="0"; fi; $(RM) -f temp.errors temp.log; test "$$x" = "1"

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(E) -n "$(C_BLUE)"C++ Compiling \"$<\"..."$(C_RESET)"
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CXXFLAGS) 2> temp.log || touch temp.errors
	$(Q)if test -e temp.errors; then echo "$(ERROR_STRING)" && cat temp.log; elif test -s temp.log; then echo "$(WARN_STRING)" && cat temp.log; else echo "$(OK_STRING)"; fi;
	$(Q)if test ! -e temp.errors; then x="1"; else x="0"; fi; $(RM) -f temp.errors temp.log; test "$$x" = "1"

Makefile.dep: $(CFILES) $(CXXFILES)
	$(E) "$(C_BLUE)"Depend"$(C_RESET)"
	$(Q)for i in $(^); do $(CXX) $(CXXFLAGS) -MM "$${i}" -MT $(OBJ_FOLDER)/`basename $${i%.*}`.o; done > $@

$(BINFILE): $(OFILES)
	$(E) "$(C_BLUE)"Linking"$(C_RESET)"
	$(Q)$(LINKER) $(LINKERFLAGS) -o $@ $(OFILES) $(LDFLAGS)

run: all
	$(Q)./$(BINFILE)

clean:
	$(E) "$(C_BLUE)"Removing files"$(C_RESET)"
	$(Q)rm -f $(BINFILE) $(OBJ_FOLDER)/* Makefile.dep
