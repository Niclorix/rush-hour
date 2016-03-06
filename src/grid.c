#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "grid.h"
#include "useful_functions.h"

struct grid_s {
        char matrice[6][6];
        game g;
};
//faire un pointeur constant plus tard

grid new_grid(game game){
	grid grid = malloc(sizeof(struct grid_s));
        grid->g = game;
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			grid -> matrice[i][j]='.';
		}
	}
	return grid;
}

void show_grid(grid grid){
	for(int abs=5;abs>=0;abs--){
		for(int ord=0; ord<6;ord++){
			char c = grid->matrice[ord][abs];
			printf("%c ", c);
		}
		printf("\n");
	}
        printf("\nNombre de mouvements : %d\n----------\n\n", game_nb_moves(grid->g));
        
}

void delete_grid(grid grid){
    delete_game(get_game(grid));
    free(grid);
}

game get_game(grid grid){
    return grid->g;
}
//demander au prof
void add_piece(grid grid, int piece_num){
    cpiece p = game_piece(get_game(grid), piece_num);
    int x = get_x(p);
    int y = get_y(p);
    set_cell_int(grid,x,y,piece_num);
    if(is_horizontal(p)){
        set_cell_int(grid,x+1,y,piece_num);
        if(get_width(p)==3){
            set_cell_int(grid,x+2,y,piece_num);
        }
    }
    else{
        set_cell_int(grid,x,y+1,piece_num);
        if(get_height(p)==3){
            set_cell_int(grid,x,y+2,piece_num);
        }
    }
}

void delete_piece_grid(grid grid, int piece_num){
    cpiece p = game_piece(get_game(grid), piece_num);
    int x = get_x(p);
    int y = get_y(p);
    set_cell_empty(grid,x,y);
    if(is_horizontal(p)){
        set_cell_empty(grid,x+1,y);
        if(get_width(p)==3){
            set_cell_empty(grid,x+2,y);
        }
    }
    else{
        set_cell_empty(grid,x,y+1);
        if(get_height(p)==3){
            set_cell_empty(grid,x,y+2);
        }
    }
}

char get_cell(grid grid, int x, int y){
    return grid->matrice[x][y];
}

void set_pieces(grid grid){
    game g = get_game(grid);
    for (int i=0; i<game_nb_pieces(g);i++){
        add_piece(grid, i);
    }
}

void set_cell_int(grid grid, int x, int y, int val){
    grid->matrice[x][y]=val+48;
}

void set_cell_empty(grid grid, int x, int y){
    grid->matrice[x][y]='.';
}

void move(grid grid, int piece_num, dir d, int distance){
    game g = grid->g;
    delete_piece_grid(grid, piece_num);
    if(play_move(g, piece_num, d, distance))
        add_piece(grid, piece_num);
    else
        add_piece(grid, piece_num);
    show_grid(grid);
}
