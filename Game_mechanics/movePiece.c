#include "movePiece.h"
#include "game.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
/*
1
2
3
4
5
6
7
8
9
 a b c d e f g h i j
*/

//lettre puis chiffre
size_t LenPossibleMovePown(struct piece **board, struct piece *p)
{
    size_t res = 0;

    int isWhite = p->isWhite ? 8 : -8;
    if (board[p->pos+isWhite] == NULL)
        res++;
    if((p->pos+isWhite-1)/8 == p->pos/8+(isWhite/8) && board[p->pos+isWhite-1] != NULL)
    {
        res++;
    }

    if((p->pos+isWhite+1)/8 == p->pos/8+(isWhite/8) && board[p->pos+isWhite+1] != NULL)
    {
        res++;
    }
    if (!p->hasMoved)
        if(board[p->pos+2*isWhite] == NULL)
            res++;
    /*
    
    if (!p->isWhite)
    {
        if (board[p->pos-8] == NULL)
            res++;
        if((p->pos-7)/8 == p->pos/8-1 && board[p->pos-7] != NULL)
            res++;
        if((p->pos-9)/8 == p->pos/8-1 && board[p->pos-9] != NULL)
            res++;
        if (!p->hasMoved)
            if(board[p->pos-16] == NULL)
                res++;
    }
    else
    {
        if (board[p->pos+8] == NULL)
            res++;
        if((p->pos+7)/8 == p->pos/8+1 && board[p->pos+7] != NULL)
            res++;
        if((p->pos+9)/8 == p->pos/8+1 && board[p->pos+9] != NULL)
            res++;
        if (!p->hasMoved)
            if(board[p->pos+16] == NULL)
                res++;
    }*/
    
    return res;
}
size_t CreatePossibleMovePown(struct piece **board, struct piece *p)
{
    size_t lenMalloc = LenPossibleMovePown(board, p);
    p->possibleMoves = malloc(sizeof(int) * lenMalloc);
    size_t cpt = 0;
    int isWhite = p->isWhite ? 8 : -8;

    if (board[p->pos+isWhite] == NULL)
    {
        p->possibleMoves[cpt] = p->pos+isWhite;
        cpt++;
    }

    if((p->pos+isWhite-1)/8 == p->pos/8+(isWhite/8) && board[p->pos+isWhite-1] != NULL)
    {
        p->possibleMoves[cpt] = p->pos+isWhite-1;
        cpt++;
    }
    
    if((p->pos+isWhite+1)/8 == p->pos/8+(isWhite/8) && board[p->pos+isWhite+1] != NULL)
    {
        p->possibleMoves[cpt] = p->pos+isWhite+1;
        cpt++;
    }

    if (!p->hasMoved)
    {
        if(board[p->pos+2*isWhite] == NULL)
        {
            p->possibleMoves[cpt] = p->pos+2*isWhite;
        }
    }
    return lenMalloc;
}
int MovePown(struct piece **board, struct piece *p, int dst)
{
    int res = 0;
    size_t lenMalloc = CreatePossibleMovePown(board, p);
    p->nbMoves = lenMalloc;
    size_t i = 0; 
    while(i < lenMalloc && !res)
    {
        if(p->possibleMoves[i] == dst)
            res = 1;
        i++;
    }
    if(board[dst] == NULL || board[dst]->isWhite != p->isWhite)
    {
        movePiece(board, p->pos, dst);
    }

    return res;
    
}
/*size_t possibleMoveTower(struct piece **board, struct piece *p)
{
    size_t numberPossibleMove = 0;
    int i = piece->pos;
    int fini = 0;
    while(i>0 && !fini)
    {
        if(board[i] == NULL)
            numberPossibleMove++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                numberPossibleMove++;
            fini = 69;
        }
        i++;
    }
    fini = 0;
    while(i<64 && !fini)
    {
        if(board[i] == NULL)
            numberPossibleMove++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                numberPossibleMove++;
            fini = 69;
        }
        i++;
    }
    fini = 0;
    while(i>0 && !fini)
    {
        if(board[i] == NULL)
            numberPossibleMove++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                numberPossibleMove++;
            fini = 69;
        }
        i++;
    }
    while(i>0 && !fini)
    {
        if(board[i] == NULL)
            numberPossibleMove++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                numberPossibleMove++;
            fini = 69;
        }
        i++;
    }

}*/