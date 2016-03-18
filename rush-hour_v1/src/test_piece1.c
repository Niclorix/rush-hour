#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "piece.h"

#define NB_PIECES 4

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
 * @return true if expected==value
 */
bool test_equality_int(int expected, int value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
 */
bool test_equality_bool(bool expected, bool value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

piece pieces[NB_PIECES];
/* configue de test

. . . . . .
. . . . . .
0 0 . . . .
3 3 . . 2 2
3 3 . 1 2 2
3 3 . 1 . .

 */
void set_up() {
  pieces[0] = new_piece(0, 3, 2, 1, true, false);  // Peut bouger de gauche à droite
  pieces[1] = new_piece(3, 0, 1, 2, false, true);  // Peut bouger de gauche à droite
  pieces[2] = new_piece(4, 1, 2, 2, true, true);   // Piece carrée qui peut bouger de haut en bas et de gauche à droite
  pieces[3] = new_piece(0, 0, 2, 3, false, false); // Piece recangulaire qui ne peut pas bouger
}
void tear_down() {
  for (int i = 0 ; i < NB_PIECES; i++)
    delete_piece(pieces[i]);
}


bool test_new_piece() {                               // MODIFICATIONS
  bool result = true;
  for (int x= 0 ; x < 5; x++)
    for (int y= 0 ; y < 5; y++)
      for (int i= 0; i < 5 ; i++)
        for (int j= 0; j < 5 ; j++)
          for (bool move_x=false; !move_x ; move_x= !move_x)
            for (bool move_y=false; !move_y ; move_y= !move_y){
              piece p = new_piece(x, y, i, j, move_x, move_y);
              result = test_equality_int(x, get_x(p),"get_x") && result;
              result = test_equality_int(y, get_y(p),"get_y") && result;
              result = test_equality_int(i, get_width(p),"get_width") && result;
              result = test_equality_int(j, get_height(p),"get_height") && result;
              result = test_equality_bool(move_x, can_move_x(p),"can_move_x") && result;
              result = test_equality_bool(move_y, can_move_y(p),"can_move_y") && result;
              delete_piece(p);
            }
   return result;
}

/* 
bool test_intersect() {                             // A faire quand intersect de piece.c sera fini
  bool result = true;
  set_up();
  for (int i=0; i < NB_PIECES; i++)
    for (int j =0; j<NB_PIECES; j++) {
      result = result && test_equality_bool(i==j, intersect(pieces[i], pieces[j]),"intersect");
    }

  piece pb_piece1 = new_piece(3, 3, false, false);
  piece pb_piece2 = new_piece(3, 1, false, false);
  result = result && test_equality_bool(true, intersect(pieces[0], pb_piece1),"intersect pb1");
  result = result && test_equality_bool(true, intersect(pb_piece2, pb_piece1),"intersect pb2");
  delete_piece(pb_piece1);
  delete_piece(pb_piece2);
  tear_down();
  return result;
}
*/

bool test_move() {                                        // MODIFICATIONS dans les for : is_horizontal devient can_move_x et !is_horizontal devient can_move_y
  bool result = true;
  piece p = new_piece(0, 0, 1, 1, true, true);
  set_up();
  for (int dist = 1; dist < NB_PIECES; dist++)
    for (int i=0; i < NB_PIECES; i++) {
      copy_piece(pieces[i],p);
      move_piece(p, LEFT, dist);
      if (can_move_x(pieces[i]))
        result = test_equality_int(get_x(pieces[i])-dist,get_x(p),"move LEFT") && result;
      else
        result = test_equality_int(get_x(pieces[i]),get_x(p),"move LEFT") && result;
      copy_piece(pieces[i],p);
      move_piece(p, RIGHT, dist);
      if (can_move_x(pieces[i]))
        result = test_equality_int(get_x(pieces[i])+dist,get_x(p),"move RIGHT") && result;
      else
        result = test_equality_int(get_x(pieces[i]),get_x(p),"move RIGHT") && result;
      copy_piece(pieces[i],p);
      move_piece(p, UP, dist);
      if (can_move_y(pieces[i]))
        result = test_equality_int(get_y(pieces[i])+dist,get_y(p),"move UP") && result;
      else
        result = test_equality_int(get_y(pieces[i]),get_y(p),"move UP") && result;
      copy_piece(pieces[i],p);
      move_piece(p, DOWN, dist);
      if (can_move_y(pieces[i]))
        result = test_equality_int(get_y(pieces[i])-dist,get_y(p),"move DOWN") && result;
      else
        result = test_equality_int(get_y(pieces[i]),get_y(p),"move DOWN") && result;


    }
  tear_down();
  delete_piece(p);
  return result;
  return false;
}


bool test_copy() {                                      // MODIFICATION new_piece
  piece p = new_piece(0, 0, 0, 0, true, true);
  bool result = true;
  set_up();
  for (int i = 0 ; i < NB_PIECES; i++) {
    copy_piece(pieces[i],p);
    result = test_equality_int(get_height(pieces[i]), get_height(p), "copy get_height") && result;
    result = test_equality_int(get_width(pieces[i]), get_width(p), "copy get_width") && result;
    result = test_equality_int(get_x(pieces[i]), get_x(p), "copy get_x") && result;
    result = test_equality_int(get_y(pieces[i]), get_y(p), "copy get_y") && result;
    result = test_equality_bool(can_move_x(pieces[i]), can_move_x(p), "copy can_move_x") && result;
    result = test_equality_bool(can_move_y(pieces[i]), can_move_y(p), "copy can_move_y") && result;
  }
  tear_down();
  delete_piece(p);
  return result;
}

int main (int argc, char *argv[])
{
  bool result= true;

  result = test_equality_bool(true, test_new_piece(), "new_piece") && result;
  //result = result && test_equality_bool(true, test_intersect(), "intersect");
  result = test_equality_bool(true, test_move(), "move") && result;
  result = test_equality_bool(true, test_copy(), "copy") && result;

  if (result){
        printf("Youpi !\n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}