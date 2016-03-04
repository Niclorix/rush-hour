CFLAGS = -Wall -g -std=c99
INCLUDE = -I include/

all:
	@make --silent sub
	@make --silent clean

sub:
	@echo Make start.
	@echo
	@gcc $(CFLAGS) src/game.c src/grid.c src/game_test1.c src/piece.c src/test_piece1.c src/affichage.c $(INCLUDE) -c
	@echo Make end.

lib:
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@ar cr lib/libgame.a game.o piece.o

game_test1:
	@make --silent sub
	@gcc game.o piece.o game_test1.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo
	@echo Executable $@-exe generated.

test_piece1:
	@make --silent sub
	@gcc game.o piece.o test_piece1.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo
	@echo Executable $@-exe generated.

affichage:
	@make --silent sub
	@gcc game.o piece.o grid.o  affichage.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo 
	@echo Executable $@-exe generated.

clean:
	@rm -f *-exe
	@make --silent clean-all-but-exe

clean-all-but-exe:
	@rm -f game.o grid.o piece.o test_piece1.o test_piece1 lib/libgame.a affichage.o game_test1.o -d lib
	@echo Files cleaned.
