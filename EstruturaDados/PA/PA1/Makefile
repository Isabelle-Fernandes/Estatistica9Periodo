C		  := gcc
C_FLAGS := 

BIN		:= bin
SRC		:= src
INCLUDE	:= include


EXECUTABLE	:= pa1.out


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(C) $(C_FLAGS) $^ -o $@

clean:
	-rm $(BIN)/*
