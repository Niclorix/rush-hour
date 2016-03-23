CFLAGS = -Wall -g -std=c99
INCLUDE = -I include/
all:
	@echo Make all start.
	@echo
	@make --silent test_game1 test_piece1 rush-hour test_game2 test_piece2 ane-rouge 
	@echo 
	@echo Make all end.

sub:
	@echo Make $(MAKEARG).
	@gcc $(CFLAGS) src/piece.c src/game.c src/test_functions.c src/$(MAKEARG).c -lm $(INCLUDE) -o $(MAKEARG)
	@echo Executable $(MAKEARG) generated.

test_game1:
	@make --silent sub MAKEARG=$@
	
test_piece1:
	@make --silent sub MAKEARG=$@
	
rush-hour:
	@make --silent sub MAKEARG=$@
	
test_game2:
	@make --silent sub MAKEARG=$@
	
test_piece2:
	@make --silent sub MAKEARG=$@
	
ane-rouge:
	@make --silent sub MAKEARG=$@
	
lib:
	@echo Make $@ start.
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@gcc $(CFLAGS) src/game.c src/piece.c $(INCLUDE) -c
	@ar cr lib/libgame.a game.o piece.o
	@rm game.o piece.o
	@echo The library libgame.a is in the directory lib.
	@echo Make $@ end.

clean:
	@rm -f *.o test_piece1 test_piece2 test_game1 test_game2 rush-hour ane-rouge lib/libgame.a -d lib 
	@echo Files cleaned.