#цель: зависимость
#[tab] команда


BIN = test
SOURCES = main.c
HEADERS = main.h
CC := gcc

all:
	$(CC) $(SOURCES) -lncurses -o $(BIN).out
$(BIN): $(HEADERS)

run: all
	./$(BIN).out

#clean:
#	rm -rf $(BIN) *.o $(BIN).out



















