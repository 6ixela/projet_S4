PACKAGE = `pkg-config --cflags --libs gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
FILE = test_function/testFunction.c Game_mechanics/game.c Game_mechanics/movePiece.c Game_mechanics/minMax.c

commit: 
	git add -A && git commit -s -m "send test" && git push

testMemory:
	gcc -Wextra -Wall -fsanitize=address -g $(FILE)

test:
	gcc -Wextra -Wall -g test_function/main.c t $(FILE)

gtk:
	gcc -Wextra -Wall -g $(PACKAGE) window.c $(FILE) $(LIBS)

clean:
	rm a.out
