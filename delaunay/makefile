#
# Delaunay Makefile
#

#
# Evan Wilde
# Makefile
#

EXEC	= delaunay


# Commands
RM	= rm -f
RMD	= $(RM) -r
CC	= gcc
CXX	= g++
TAR	= tar
MKDIR	= mkdir -p

# Directories
SRC	= src/
BUILD	= build/
BIN	= bin/
LIB	= libs/
INC	= inc/

# Thing includes/glfw-cxx


# Flags
CFLAGS 	= -c -g -pthread
CXFLAGS	= $(CFLAGS) -std=c++11
LIBS	= -pthread -lglfw -lGL -L${LIB} -lglfw-cxx

# Source Files
SRCS	= \
	  $(wildcard $(SRC)*.c) \
	  $(wildcard $(SRC)*.C) \
	  $(wildcard $(SRC)*.cc) \
	  $(wildcard $(SRC)*.cpp)

# Object Files
OBJS	= \
	  $(patsubst $(SRC)%.c, $(BUILD)%.o, \
	  $(patsubst $(SRC)%.C, $(BUILD)%.o, \
	  $(patsubst $(SRC)%.cc, $(BUILD)%.o, \
	  $(patsubst $(SRC)%.cpp, $(BUILD)%.o, $(SRCS)))))

.PHONY: all rebuild clean

all: $(BUILD) $(BIN) $(BIN)$(EXEC)

rebuild: clean all

clean:
	$(RM) $(BUILD)*.o
	$(RM) $(BIN)$(EXEC)

$(BIN):
	$(MKDIR) $(BIN)

$(BUILD):
	$(MKDIR) $(BUILD)

$(BUILD)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -I $(INC) $< -o $@

$(BUILD)%.o: $(SRC)%.C
	$(CXX) $(CXFLAGS) -I $(INC) $< -o $@

$(BUILD)%.o: $(SRC)%.cc
	$(CXX) $(CXFLAGS) -I $(INC) $< -o $@

$(BUILD)%.o: $(SRC)%.cpp
	$(CXX) $(CXFLAGS) -I $(INC) $< -o $@

# Link executable
$(BIN)$(EXEC): $(OBJS) $(INC)*
	$(CXX) -o $@ $< $(LIBS)
