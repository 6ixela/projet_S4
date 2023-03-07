#include <stddef.h>
#include "game.h"
#ifndef MOVEPIECE_H
#define MOVEPIECE_H

size_t LenPossibleMovePown(struct piece **board, struct piece *p);
void CreatePossibleMovePown(struct piece **board, struct piece *p);

size_t LenPossibleMoveTower(struct piece **board, struct piece *p);
void CreatePossibleMoveTower(struct piece **board, struct piece *p);

void MovePiece(struct piece **board, struct piece *p, int dst);
int Move(struct piece **board, struct piece *p, int dst);

size_t LenPossibleMoveKing(struct piece **board, struct piece *p);
void CreatePossibleMoveKing(struct piece **board, struct piece *p);

size_t LenPossibleMoveKnight(struct piece **board, struct piece *p);
void CreatePossibleMoveKnight(struct piece **board, struct piece *p);

size_t LenPossibleMoveBishop(struct piece **board, struct piece *p);
void CreatePossibleMoveBishop(struct piece **board, struct piece *p, size_t cpt);
void printMove(struct piece *p);

void CreatePossibleMoveQueen(struct piece **board, struct piece *p);
#endif