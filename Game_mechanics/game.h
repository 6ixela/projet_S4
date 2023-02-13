#ifndef GAME_H
#define GAME_H

struct piece 
{
    char *name;
    int isWhite;
    int hasMoved;
    int value;
    int pos;
    int nbMoves;
    int *possibleMoves;
};

//initializes a new piece with the given name
//returns null if wrong name
struct piece *newPiece (char* name);

//free the piece p
void freePiece(struct piece *p);

//Creates a new board and places every base piece on it
//returns the board(a list of pointers of pieces)
struct piece **newBoard();

//Free the board
void freeBoard(struct piece **board);

//Places a piece at a given place
//board: the board to place; name: the piece name; pos: the position to place
//returns 0 if worked, -1 if position problem, 1 if there is already a piece
int placePiece(struct piece **board, char* name, int pos);

//Moves a piece from pos to dest
//if no piece in pos or dest not in the pieces possible Moves, does nothing
void movePiece(struct piece **board, int pos, int dest);

#endif
