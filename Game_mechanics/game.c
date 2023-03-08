#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "movePiece.h"


struct piece *newPiece(char *name)
{
    struct piece *res =  malloc(sizeof(struct piece));
    size_t len = strlen(name) + 1;
    if(strncmp(name, "pawn", len) == 0)
        res->value = 100;
    else if (strncmp(name, "knight", len) == 0)
        res->value = 300;
    else if (strncmp(name, "bishop", len) == 0)
        res->value = 300;
    else if (strncmp(name, "rook", len) == 0)
        res->value = 500;
    else if (strncmp(name, "queen", len) == 0)
        res->value = 900;
    else if (strncmp(name, "king", len) != 0)
    {
        free(res);
        res = NULL;
    }
    if(res)
    {
        res->hasMoved = 0;
        res->isWhite = 0;
        res->name = malloc(len);
        res->possibleMoves = malloc(0);
        memcpy(res->name, name, len);
    }
    return res;
}

void freePiece(struct piece *p)
{
    free(p->name);

    free(p->possibleMoves);
    
    free(p);
}

struct piece **newBoard()
{
    //malloc board size: 64 pointers
    struct piece **board = malloc(sizeof(struct piece*) * 64);
    for (int i = 0; i<64; i++)
    {
        board[i] = NULL;
    }

    //list to place pieces
    char piecesNames[][10] = {"rook", "knight", "bishop", "queen", "king",
    "bishop", "knight", "rook"};

    for(int x = 0; x<8; x++)
    {
        int posW1 = 8+x;
        int posW2 = x;
        int posB1 = 48+x;
        int posB2 = 56+x;
        //place pawns
        placePiece(board, "pawn", posW1);
        placePiece(board, "pawn", posB1);
        board[posW1]->isWhite = 1;

        //place others
        placePiece(board, piecesNames[x], posW2);
        placePiece(board, piecesNames[x], posB2);
        board[posW2]->isWhite = 1;
    }

    return board;
}

void freeBoard(struct piece **board)
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            struct piece *p = board[i * 8 + j];
            if (p != NULL)
            {
                freePiece(p);
            }   
        }   
    }
    free(board);
}

int placePiece(struct piece **board, char* name, int pos)
{
    int res = 0;
    if(pos < 0 || pos > 63)
    {
        printf("place_piece: Error in position\n");
        res = -1;
    }
    else if(board[pos] != NULL)
    {
        printf("place_piece: A piece is already there!\n");
        res = 1;
    }
    else
    {
        board[pos] = newPiece(name);
        board[pos]->pos = pos;
    }
    return res;
}

int movePiece(struct piece **board, int pos, int dest)
{
    struct piece *piece = board[pos];
    int res = 0;
    if(piece != NULL)
    {
        int isPossible = 0;
        int i =0;
        while(i<piece->nbMoves && !isPossible)
        {
            isPossible = piece->possibleMoves[i] == dest;
            i++;
        }
        if(isPossible)
        {
            if(board[dest] != NULL)
            {
                //eats the piece on the position
                freePiece(board[dest]);
            }
            board[dest] = piece;
            board[pos] = NULL;
            piece->hasMoved = 1;
            piece->pos = dest;
        }
        res = isPossible;
    }
    return res;
}

void turn(struct piece **board, int isWhiteTurn)
{
    
    while(1)
    {
        printf("Enter piece position then destinaton:\n");
        char* piecePos = calloc(3, 1);
        char* dest = calloc(3, 1);
        fgets(piecePos, 3, stdin);
        fgets(dest, 3, stdin);

        if(piecePos[0] < 'a' || piecePos[0] > 'h' || 
            piecePos[1] < '1' || piecePos[1] > '8' )
        {
            printf("incorrect character. ");
            continue;
        }
        int p1 = (piecePos[0] - 'a')*8 + piecePos[0] - '1';
        int p2 = (piecePos[1] - 'a')*8 + piecePos[1] - '1';

        if(movePiece(board, p1,p2))
            break;
        printf("Position not accessible. ");
    }
    //TODO: CALCUTALE ALL POS FOR OTHER PLAYER
    //int nextMoves = CalculateColorMoves(board, !isWhiteTurn)
    //if nextmoves = 0 => won game


    //calls again for next turn from other player
    turn(board, !isWhiteTurn);
}