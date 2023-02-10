commit: 
	git add -A && git commit -s -m "send test" && git push

test:
	gcc -Wextra -Wall test_function/testFunction.c Game_mechanics/game.c

clean:
	rm a.out
