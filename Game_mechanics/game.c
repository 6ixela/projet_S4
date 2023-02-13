#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


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
        memcpy(res->name, name, len);
    }
    return res;
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
                free(p->name);
                free(p);
            }   
        }   
    }  
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
    }
    return res;
}

void movePiece(struct piece **board, int pos, int dest)
{
    struct piece *piece = board[pos];
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
                //MANGER
            }
            board[dest] = piece;
            board[pos] = NULL;
        }
    }
}
