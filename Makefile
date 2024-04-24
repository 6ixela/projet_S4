PACKAGE = `pkg-config --cflags --libs gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
FILE = test_function/testFunction.c Game_mechanics/game.c Game_mechanics/movePiece.c Game_mechanics/minMax.c
CC=gcc
testMemory:
	$(CC) -Wextra -Wall -fsanitize=address -g $(FILE)

test:
	$(CC) -Wextra -Wall -g test_function/main.c $(FILE)

gtk:
	$(CC) -Wextra -Wall -g $(PACKAGE) window.c $(FILE) $(LIBS)

clean:
	rm a.out
