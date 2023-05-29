#include "minMax.h"
#include "movePiece.h"
#include "game.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


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

struct piece *pieceCopy(struct piece *p)
{
    struct piece *res = newPiece(p->name);
    res->hasMoved = p->hasMoved;
    res->isWhite = p->isWhite;
    res->nbMoves = p->nbMoves;
    res->pos = p->pos;
    res->value = p->value;
    res->possibleMoves = malloc(sizeof(int) * p->nbMoves);
    for(int i = 0; i<p->nbMoves;i++)
    {
        res->possibleMoves[i] = p->possibleMoves[i];
    }
    return res;
}

struct piece *tempMove(struct piece **board, int pos, int dest,
    struct piece **eatenDup)
{
    struct piece *p = board[pos];
    struct piece *dup = pieceCopy(p);
    board[pos] = dup;
    if(board[dest]) //eats so need to save the piece eaten
    {
        *eatenDup = pieceCopy(board[dest]);
    }
    movePiece(board, pos,dest);
    return dup;
}

void undoMove(struct piece **board, struct piece *p, struct piece *dup,
     struct piece *eatenDup)
{
    board[dup->pos] = NULL;
    freePiece(dup);
    if(eatenDup != NULL)
    {
        board[eatenDup->pos] = eatenDup;
    }
    board[p->pos] = p;
}

int minmax(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos)
{
    int res;
    if (depth == 0)
    {
        res = evalBoard(board);
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
                
                for (int k = 0; k < p->nbMoves; k++)
                {
                    struct piece **newboard = deepCopy(board);
                    movePiece(newboard, p->pos, p->possibleMoves[k]);
                    int val = minmax(newboard, depth-1, !isWhite, 0,NULL,NULL);
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
            if(!isCheck(board, isWhite))
            {
                best = 0;
            }
        }
        res = best;
    }
    return res;
}


struct move
{
    int start;
    int dest;
    struct piece *p;
    struct piece *eaten;
};

struct move *newMove(struct piece **board, int start, int dest)
{
    struct move *res = malloc(sizeof(struct move));
    res->start = start;
    res->dest = dest;
    res->p = board[start];
    res->eaten = board[dest];
    return res;
}

int minmaxOptiV2(struct piece **board, int depth, int isWhite, int returnMove, 
int *startPos, int *destPos)
{

    int res;
    if (depth == 0)
    {
        res = evalBoard(board);
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
                
                for (int k = 0; k < p->nbMoves; k++)
                {
                   struct move *m = newMove(board, p->pos, p->possibleMoves[k]);
                   board[m->start] = pieceCopy(p);
                   movePieceNoFree(board, p->pos, p->possibleMoves[k]);
                   int val = minmaxOptiV2(board, depth-1, !isWhite, 0,NULL,NULL);
                   free(board[m->dest]);
                   board[m->dest] = m->eaten;
                   board[m->start] = p;
                   free(m);

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
            if(!isCheck(board, isWhite))
            {
                best = 0;
            }
        }
        res = best;
    }
    return res;
}