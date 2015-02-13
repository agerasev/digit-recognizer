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

all: $(BIN)

$(BIN): $(OBJ)
	g++ -g -o $@ $^

obj/%.cpp.o : src/%.cpp $(HDR)
	g++ -g -Wall -std=c++11 -c $< -o $@

obj/%.c.o : src/%.c $(HDR)
	gcc -g -Wall -c $< -o $@
	
clear:
	rm $(BIN); rm $(OBJ)
