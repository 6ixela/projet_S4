#include "game.h"
#include "../test_function/testFunction.h"

#ifndef MINMAX_H
#define MINMAX_H
int evalBoard(struct piece **board);

struct piece **deepCopy(struct piece **board);

//algo minmax, retourne l'évaluation et stock le meilleur mouvement trouvé dans
//startpos et destpos. Appeler avec returnmove à true
int minmax(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos);
#endif
