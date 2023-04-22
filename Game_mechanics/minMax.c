#include "minMax.h"
#include "movePiece.h"
#include "game.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int cpt = 0;

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
            /*if(strncmp(p->name, "pawn", len) == 0)
                res += p->value * pos;
            else if (strncmp(p->name, "knight", len) == 0)
                res += p->value * pos;
            else if (strncmp(p->name, "bishop", len) == 0)
                res += p->value * pos;
            else if (strncmp(p->name, "rook", len) == 0)
                res += p->value * pos;
            else if (strncmp(p->name, "queen", len) == 0)
                res += p->value * pos;
            */
           printf("value of %s = %d -> %d\n", p->name, p->value, p->value * pos);
           res += p->value * pos;
           printf("res = %d\n", res);
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
                pNew->nbMoves = p->nbMoves;
                free(pNew->possibleMoves);
                pNew->possibleMoves = malloc(sizeof(int)* p->nbMoves);
                for (int i = 0; i < p->nbMoves; i++)
                {
                    pNew->possibleMoves[i] = p->possibleMoves[i];
                }
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
    cpt++;
    printf("board of n%d (depth = %d):\n", cpt, depth);
    print_chessv2(board);
    fflush(stdout);
    int res;
    if (depth == 0)
    {
        printf("leaf of n%d: return = ", cpt);
        fflush(stdout);
        res = evalBoard(board);
        printf("%d\n", res);
        fflush(stdout);
    }
    else
    {
        int best = INT_MAX;
        if (isWhite)
            best = INT_MIN;
        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *p = board[i * 8 + j];
                
                if (p == NULL || p->isWhite != isWhite)
                    continue;
                
                for (size_t k = 0; k < p->nbMoves; k++)
                {
                    struct piece **newboard = deepCopy(board);
                    int moved=movePiece(newboard, p->pos, p->possibleMoves[k]);
                    //printf("moved = %d\n",moved);
                    int val = minmax(newboard, depth-1, !isWhite, 0,NULL,NULL);
                    //printf("val = %d\n", val);
                    freeBoard(newBoard());
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
            }
            
        }
        if(best == INT_MAX || best == INT_MIN)
        {
            printf("leaf of n%d (no moves): return = ", cpt);
            fflush(stdout);
            if(!isCheck(board, isWhite))
            {
                best = 0;
            }
            printf("%d at depth %d\n", best, depth);
            fflush(stdout);
        }
        res = best;
    }
    return res;
}