#ifndef TESTFUNCTION_H
#define TESTFUNCTION_H

char *recupPiece(struct piece *p);
void print_chess(struct piece **tab);

//meme que au dessus mais print les numéros de case
char *recupPiecev2(struct piece *p, int pos);
void print_chessv2(struct piece **tab);

//créé board a partir d'un string fen
struct piece **LoadFromFen(char* fen);

//test tous les moves d'une certaine profondeur(prof = 2 pour 1 tour de chaque)
int testAllMoves(struct piece **board, int depth, int isWhite);

#endif