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

void undoMove(struct piece **board, struct move *m);

//algo minmax, retourne l'évaluation et stock le meilleur mouvement trouvé dans
//startpos et destpos. Appeler avec returnmove à true
int minmax(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos);

int minmaxV2(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos, int alpha, int beta);

int minmaxOptiV2(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos);

int minmaxOptiV3(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos, int alpha, int beta);
#endif
