commit: 
	git add -A && git commit -s -m "send test" && git push

testMemory:
	gcc -Wextra -Wall -fsanitize=address test_function/testFunction.c Game_mechanics/game.c

test:
	gcc -Wextra -Wall test_function/testFunction.c Game_mechanics/game.c Game_mechanics/movePiece.c

clean:
	rm a.out
