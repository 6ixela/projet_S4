#include <stddef.h>
#include "game.h"
#ifndef MOVEPIECE_H
#define MOVEPIECE_H

size_t LenPossibleMovePown(struct piece **board, struct piece *p);
size_t CreatePossibleMovePown(struct piece **board, struct piece *p);
int MovePown(struct piece **board, struct piece *p, int dst);

size_t LenPossibleMoveTower(struct piece **board, struct piece *p);
void CreatePossibleMoveTower(struct piece **board, struct piece *p);



#endif