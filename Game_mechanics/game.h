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
//returns 0 if movement was not possible
int movePiece(struct piece **board, int pos, int dest);

//used to be able to not filter moves. else use movePiece
int __movePiece(struct piece **board, int pos, int dest, int filterMoves);

//used to play the game in the console
void turn(struct piece **board, int isWhiteTurn);

//Calculates the possible moves of all pieces of a color and stores it in the
//pieces. returns number of moves found for testing
int CalculateColorMoves(struct piece** board, int isWhite, int filterMoves);

//filters the moves of a piece to remove impossible ones (that leaves in check)
void FilterMoves(struct piece **board, struct piece *p);

//tests if a move makes the mover be in check (used for FilterMoves)
int TestCheckmate(struct piece **board ,struct piece *piece, int dest);

//verify if king of a color is in check
int isCheck(struct piece **board, int isWhite);
#endif
