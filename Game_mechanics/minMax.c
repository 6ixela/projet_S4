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
            
            if (p == NULL)
                continue;
            //pos permet de savoir si piece blanche ou noir
            short pos = p->isWhite ? 1 : -1;
            
            
            size_t len = strlen(p->name);
            if(strncmp(p->name, "pawn", len) == 0)
                res += p->value * pos;
            else if (strncmp(p->name, "knight", len) == 0)
                res += p->value * pos;
            else if (strncmp(p->name, "bishop", len) == 0)
                res += p->value * pos;
            else if (strncmp(p->name, "rook", len) == 0)
                res += p->value * pos;
            else if (strncmp(p->name, "queen", len) == 0)
                res += p->value * pos;
        }
        
    }
    
    return res;
}

struct piece **deepCopy(struct piece **board)
{
    struct piece **boardcopy = malloc(sizeof(struct piece*) * 64);
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            struct piece *p = board[i * 8 + j];
            if(p)
            {
                boardcopy[i * 8 + j] = newPiece(p->name);
                struct piece *pNew = boardcopy[i * 8 + j];
                pNew->hasMoved = p->hasMoved;
                pNew->isWhite = p->isWhite;
                pNew->pos = p->pos;
                pNew->value = p->value;
                boardcopy[i*8+j] = pNew;
            }
            else
                boardcopy[i*8+j] = NULL;
        }
        
    }
    
    return boardcopy;
}

int minmax(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos)
{
    int res = NULL;
    if (depth == 0)
        res = evalBoard(board);
    else
    {
        int best = NULL;
        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *p = board[i * 8 + j];
                
                if (p == NULL || p->isWhite != isWhite)
                    continue;
                
                for (size_t k = 0; k < p->nbMoves; p++)
                {
                    struct piece **newboard = deepCopy(board);
                    movePiece(newboard, p->pos, p->possibleMoves[k]);
                    int val = minmax(newboard, depth-1, !isWhite, 0,NULL,NULL);
                    if(best)
                    {
                        if(isWhite)
                        {
                            if(val > best)
                            {
                                best = val;
                                if(returnMove)
                                {
                                    *startPos = p->pos;
                                    *destPos = p->possibleMoves[k];
                                }
                            }
                        }
                        else
                        {
                            if(val < best)
                            {
                                best = val;
                                if(returnMove)
                                {
                                    *startPos = p->pos;
                                    *destPos = p->possibleMoves[k];
                                }
                            }
                        }
                    }
                    else   
                        best = val;
                }
            }
            
        }
        if(best == NULL)
        {
            printf("TODO: minMax.c line 127\n");
            //TODO: pas de move possible: si draw 0 sinon -inf
        }
        res = best;
    }
    return res;
}