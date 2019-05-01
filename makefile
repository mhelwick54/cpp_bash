TARGET=bash
CXXFLAGS=-Wall -std=c++17 -lstd++fs
OPT_LVL=
LDFLAGS=-I$(IDIR)

IDIR=./include
SDIR=./src
ODIR=./bin

COM_COLOR=\033[0;34m
OBJ_COLOR=\033[0;36m
NO_COLOR=\033[m
OK_COLOR=\033[0;32m
ERROR_COLOR=\033[0;31m
WARN_COLOR=\033[0;33m

COM_STRING="Compiling"
OK_STRING="[OK]"
ERROR_STRING="[ERROR]"
WARN_STRING="[WARNING]"

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	ifeq ($(shell which g++-8), /usr/local/bin/g++-8)
		CXX=g++-8#MacOS GNU gcc, not clang
	else
		CXX=clang
	endif
else
	CXX=g++#GNU gcc
endif

$(info Compiling with $(CXX))

_DEPS=main.h parser.h command.h debug.h funcs.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_SRC=main.cpp parser.cpp command.cpp funcs.cpp
SRC=$(patsubst %,$(SDIR)/%,$(_SRC))

_OBJ=main.o parser.o command.o funcs.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

define make_pretty
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

all: $(ODIR)/$(TARGET)
	$(info DEP = $(DEPS))
	$(info SRC = $(SRC))
	$(info OBJ = $(OBJ))
	@printf "%b" "Compilation successful\n"

$(ODIR)/$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) $(OPT_LVL) $(LDFLAGS) $^ -o $@
	@$(call make_pretty)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(CFLAGS) $(OPT_LVL) -MMD -c $< -o $@
	@$(call make_pretty)

.PHONY: clean

clean:
	@printf "%-40b%b" "$(COM_COLOR)Cleaning object directory" "$(OBJ_COLOR)rm -f -r $(ODIR)/*$(NO_COLOR)\n"
	@rm -f -r $(ODIR)/*
