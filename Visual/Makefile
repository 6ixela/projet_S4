
CC = gcc
CFLAGS += `pkg-config --cflags gtk+-3.0`
LIBS += `pkg-config --libs gtk+-3.0`

all: window

window: window.c ./Game_mechanics/game.c ./Game_mechanics/minMax.c ./Game_mechanics/movePiece.c ./test_function/testFunction.c
	$(CC) $(CFLAGS) -o window window.c $(LIBS)

clean:	rm -f window

