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

int minmaxOpti(struct piece **board, int depth, int isWhite, int returnMove, 
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
                    
                    struct piece *eatenDup = NULL;
                    struct piece *dup = NULL;
                    printf("effective pos = %d, pos in p = %d\n", i * 8 + j, p->pos);
                    printf("test0, pos = %d, dest = %d\n", p->pos, p->possibleMoves[k]);
                    fflush(stdout);
                    dup = tempMove(board,p->pos,p->possibleMoves[k],&eatenDup);
                    printf("test1\n");
                    printf("BEFORE : p = %s at %d, dup = %s at %d\n", p->name, p->pos, dup->name,dup->pos);
                    fflush(stdout);
                    int val = minmax(board, depth-1, !isWhite, 0,NULL,NULL);
                    if(val == -1)
                    {
                        printf("returned -1 at pos %d to %d\n", p->pos, p->possibleMoves[k]);
                        fflush(stdout);
                        return -1;
                    }
                    printf("test2\n");
                    fflush(stdout);
                    
                    //print_chessv2(board);
                    printf("AFTER: p = %s at %d, dup = %s at %d\n", p->name, p->pos, dup->name,dup->pos);
                    fflush(stdout);
                    undoMove(board, p, dup, eatenDup);
                    printf("test3\n");
                    
                    //print_chessv2(board);
                    fflush(stdout);
                    
                    //if(p->pos == 50 && p->possibleMoves[k] == 42 && board[18] !=NULL)
                    //    print_chessv2(board);
                    
                    CalculateColorMoves(board, isWhite, 1);
                    CalculateColorMoves(board, !isWhite, 1);

                    
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