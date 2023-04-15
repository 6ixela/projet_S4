#include "minMax.h"
#include "movePiece.h"
#include "game.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int evalBoard(struct piece **board)
{
    int res = 0;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            struct piece *p = board[i * 8 + j];
            //pos permlet de savoir si piece blanche ou noir
            char pos = p->isWhite ? 1 : -1;

            size_t len = strlen(p->name);
            if(strncmp(p->name, "pawn", len) == 0)
                res = 1 * pos;
            else if (strncmp(p->name, "knight", len) == 0)
                res = 2 * pos;
            else if (strncmp(p->name, "bishop", len) == 0)
                res = 3 * pos;
            else if (strncmp(p->name, "rook", len) == 0)
                res = 7 * pos;
            else if (strncmp(p->name, "queen", len) == 0)
                res =20 * pos;
            else if(strncmp(p->name, "king", len) == 0)
                res = 100 * pos;
            
        }
        
    }
    
    return res;
}

struct piece **deepCopy(struct piece **board)
{
    struct piece **boardcopy = malloc(sizeof(struct piece*) * 64);
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; i++)
        {

            boardcopy[i * 8 + j] = malloc(sizeof(struct piece));
            struct piece *p = board[i * 8 + j];
            struct piece *pNew = newPiece(p->name);
            pNew->hasMoved = p->hasMoved;
            pNew->isWhite = p->isWhite;
            pNew->pos = p->pos;
            pNew->value = p->value;
        }
        
    }
    
    return boardcopy;
}