HDR = \
	src/misc.h \
	src/linalg.h \
	src/network.h \
	src/network_gd.h \
	src/reader.hpp
	
SRC = \
	src/main.cpp \
	src/linalg.c \
	src/network.c \
	src/network_gd.c
	
OBJ = $(SRC:src/%=obj/%.o)
BIN = bin/reco

LINK_FLAGS =   
CXX_FLAGS =    -std=c++11
C_FLAGS =      
COMMON_FLAGS = -Wall

all: $(BIN)

$(BIN): $(OBJ)
	g++ $(LINK_FLAGS) -o $@ $^

obj/%.cpp.o : src/%.cpp $(HDR)
	g++ $(COMMON_FLAGS) $(CXX_FLAGS) -c $< -o $@

obj/%.c.o : src/%.c $(HDR)
	gcc $(COMMON_FLAGS) $(C_FLAGS) -c $< -o $@
	
clear:
	rm $(BIN); rm $(OBJ)
