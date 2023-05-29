#include "game.h"
#include "../test_function/testFunction.h"

#ifndef MINMAX_H
#define MINMAX_H


//evaluates the board
int evalBoard(struct piece **board);

//makes a deepcopy of the board
struct piece **deepCopy(struct piece **board);

//makes a copy of a piece
struct piece *pieceCopy(struct piece *p);

//makes a temporary move, returns a copy of the original piece and stores 
//the eaten piece if there is one
struct piece *tempMove(struct piece **board, int pos, int dest,
    struct piece **eatenDup);

//undo a temporary move with the copy made by it and the eaten piece if one
void undoMove(struct piece **board, struct piece *p, struct piece *dup,
    struct piece *eatenDup);

//algo minmax, retourne l'évaluation et stock le meilleur mouvement trouvé dans
//startpos et destpos. Appeler avec returnmove à true
int minmax(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos);

int minmaxOptiV2(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos);
#endif
