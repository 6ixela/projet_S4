PACKAGE = `pkg-config --cflags --libs gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

commit: 
	git add -A && git commit -s -m "send test" && git push

testMemory:
	gcc -Wextra -Wall -fsanitize=address -g test_function/testFunction.c Game_mechanics/game.c Game_mechanics/movePiece.c Game_mechanics/minMax.c

test:
	gcc -Wextra -Wall -g test_function/main.c test_function/testFunction.c Game_mechanics/game.c Game_mechanics/movePiece.c Game_mechanics/minMax.c

gtk:
	gcc -Wextra -Wall -g $(PACKAGE) test_function/window.c test_function/testFunction.c Game_mechanics/game.c Game_mechanics/movePiece.c Game_mechanics/minMax.c

clean:
	rm a.out
