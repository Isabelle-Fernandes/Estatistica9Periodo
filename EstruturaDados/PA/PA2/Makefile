CXX        := g++
CXX_FLAGS  := -Wall -Wextra -std=c++17 -ggdb

BIN        := bin
SRC        := src
INCLUDE    := include

EXECUTABLE := pa2.out

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
