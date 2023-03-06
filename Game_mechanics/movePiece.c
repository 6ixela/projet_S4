#include "movePiece.h"
#include "game.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
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
size_t LenPossibleMovePawn(struct piece **board, struct piece *p)
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
    
    return res;
}
void CreatePossibleMovePawn(struct piece **board, struct piece *p)
{
    p->nbMoves = LenPossibleMoveTower(board, p);
    free(p->possibleMoves);
    p->possibleMoves = malloc(sizeof(int) * p->nbMoves);
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
}

size_t LenPossibleMoveTower(struct piece **board, struct piece *p)
{
    size_t numberPossibleMove = 0;
    int i = p->pos - 8;
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
        i-=8;
    }
    i = p->pos +8;
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
        i+=8;
    }
    i = p->pos + 1;
    fini = 0;
    while(i/8==p->pos/8 && !fini)
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
    i = p->pos-1;
    fini = 0;

    while(i >= 0 && i/8==p->pos/8 && !fini)
    {
        if(board[i] == NULL)
            numberPossibleMove++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                numberPossibleMove++;
            fini = 69;
        }
        i--;
    }
    return numberPossibleMove;
}

void CreatePossibleMoveTower(struct piece **board, struct piece *p)
{
    p->nbMoves = LenPossibleMoveTower(board, p);
    free(p->possibleMoves);
    p->possibleMoves = malloc(sizeof(int) * p->nbMoves);
    size_t cpt = 0;
    int i = p->pos-8;
    int fini = 0;
    while(i>0 && !fini)
    {
        if(board[i] == NULL)
        {
            p->possibleMoves[cpt] = i;
            cpt++;
        }
        else
        {
            if (board[i]->isWhite != p->isWhite)
            {
                p->possibleMoves[cpt] = i;
                cpt++;
            }
            fini = 69;
        }
        i-=8;
    }

    i = p->pos+8;
    fini = 0;
    while(i<64 && !fini)
    {

        if(board[i] == NULL)
        {
            p->possibleMoves[cpt] = i;
            cpt++;
        }
        else
        {
            if (board[i]->isWhite != p->isWhite)
            {
                p->possibleMoves[cpt] = i;
                cpt++;
            }
            fini = 69;
        }
        i+=8;
    }

    i = p->pos+1;
    fini = 0;
    while(i/8==p->pos/8 && !fini)
    {
        if(board[i] == NULL)
        {
            p->possibleMoves[cpt] = i;
            cpt++;
        }
        else
        {
            if (board[i]->isWhite != p->isWhite)
            {
                p->possibleMoves[cpt] = i;
                cpt++;
            }
            fini = 69;
        }
        i++;
    }

    i = p->pos-1;
    fini = 0;
    while(i >= 0 && i/8==p->pos/8 && !fini)
    {
        if(board[i] == NULL)
        {
            p->possibleMoves[cpt] = i;
            cpt++;
        }
        else
        {
            if (board[i]->isWhite != p->isWhite)
            {
                p->possibleMoves[cpt] = i;
                cpt++;
            }
            fini = 69;
        }
        i--;
    }
}



void MovePiece(struct piece **board, struct piece *p, int dst)
{
      
    if(board[dst] != NULL)
        //eats the piece on the position
        freePiece(board[dst]);
    board[dst] = p;
    board[p->pos] = NULL;
    p->hasMoved = 1;
    p->pos = dst;
}



size_t LenPossibleMoveKing(struct piece **board, struct piece *p)
{
    size_t res = 0;

    if(p->pos + 8 < 64 && (board[p->pos + 8] == NULL ||
    board[p->pos + 8]->isWhite != p->isWhite))
        res++;
    if(p->pos - 8 > 0 && (board[p->pos - 8] == NULL ||
    board[p->pos - 8]->isWhite != p->isWhite))
        res++;
    if(p->pos + 9 < 64 && (board[p->pos + 9] == NULL ||
    board[p->pos + 9]->isWhite != p->isWhite))
        res++;
    if(p->pos + 7 < 64 && (board[p->pos + 7] == NULL ||
    board[p->pos + 7]->isWhite != p->isWhite))
        res++;
    if(p->pos - 7 > 0 && (board[p->pos - 7] == NULL ||
    board[p->pos - 7]->isWhite != p->isWhite))
        res++;
    if(p->pos - 9 > 0 && (board[p->pos - 9] == NULL ||
    board[p->pos - 9]->isWhite != p->isWhite))
        res++;
    if((p->pos + 1)/8 == p->pos&& (board[p->pos + 1] == NULL ||
    board[p->pos + 1]->isWhite != p->isWhite))
        res++;
    if(p->pos - 1 >= 0 && (p->pos - 1)/8 == p->pos &&
    (board[p->pos - 1] == NULL || board[p->pos - 1]->isWhite != p->isWhite))
        res++;
    return res;
}

void CreatePossibleMoveKing(struct piece **board, struct piece *p)
{
    p->nbMoves = LenPossibleMoveKing(board, p);
    free(p->possibleMoves);
    p->possibleMoves = malloc(sizeof(int) * p->nbMoves);
    size_t cpt = 0;
    if(p->pos + 8 < 64 && (board[p->pos + 8] == NULL ||
    board[p->pos + 8]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 8;
        cpt++;
    }
    if(p->pos - 8 > 0 && (board[p->pos - 8] == NULL ||
    board[p->pos - 8]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos - 8;
        cpt++;
    }
    if(p->pos + 9 < 64 && (board[p->pos + 9] == NULL ||
    board[p->pos + 9]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 9;
        cpt++;
    }
    if(p->pos + 7 < 64 && (board[p->pos + 7] == NULL ||
    board[p->pos + 7]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 7;
        cpt++;
    }
    if(p->pos - 7 < 64 && (board[p->pos - 7] == NULL ||
    board[p->pos - 7]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos - 7;
        cpt++;
    }
    if(p->pos - 9 < 64 && (board[p->pos - 9] == NULL ||
    board[p->pos - 9]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos - 9;
        cpt++;
    }
    if((p->pos + 1)/8 == p->pos&& (board[p->pos + 1] == NULL ||
    board[p->pos + 1]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 1;
        cpt++;
    }
    if(p->pos - 1 >= 0 && (p->pos - 1)/8 == p->pos &&
    (board[p->pos - 1] == NULL || board[p->pos - 1]->isWhite != p->isWhite))
        p->possibleMoves[cpt] = p->pos - 1;
}

int Move(struct piece **board, struct piece *p, int dst)
{
    int res = 0;
    if(p != NULL)
    {
        size_t len = strlen(p->name);
        if(strncmp(p->name, "pawn", len) == 0)
            CreatePossibleMovePawn(board, p);

        else if (strncmp(p->name, "knight", len) == 0)
            CreatePossibleMoveKnight(board, p);
        else if (strncmp(p->name, "bishop", len) == 0)
            CreatePossibleMoveKing(board, p);

        else if (strncmp(p->name, "rook", len) == 0)
            CreatePossibleMoveTower(board, p);

        else if (strncmp(p->name, "queen", len) == 0)
            CreatePossibleMoveKing(board, p);
    
        else if(strncmp(p->name, "king", len) == 0)
            CreatePossibleMoveKing(board, p);
        
        size_t i = 0; 
        printMove(p);

        while((int)i < p->nbMoves && !res)
        {
            if(p->possibleMoves[i] == dst)
                res = 1;
            i++;
        }
        if(res && (board[dst] == NULL || board[dst]->isWhite != p->isWhite))
            MovePiece(board, p, dst);
    }
    return res;
}

void CreatePossibleMoveKnight(struct piece **board, struct piece *p)
{
    p->nbMoves = LenPossibleMoveKnight(board, p);
    free(p->possibleMoves);
    p->possibleMoves = malloc(sizeof(int) * p->nbMoves);
    size_t cpt = 0;
    if(p->pos-17 > 0 && (p->pos-17)/8+2 == p->pos/8 &&
    (board[p->pos -17] == NULL || board[p->pos - 17]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos -17;
        cpt++;
    }
    if(p->pos-15 > 0 && (p->pos-15)/8+2 == p->pos/8 &&
    (board[p->pos-15] == NULL || board[p->pos-15]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos -15;
        cpt++;
    }
    if(p->pos-10 > 0 && (p->pos-10)/8+1 == p->pos/8 &&
    (board[p->pos-10] == NULL || board[p->pos-10]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos -10;
        cpt++;
    }
    if(p->pos-6 > 0 && (p->pos-6)/8+1 == p->pos/8 &&
    (board[p->pos-6] == NULL || board[p->pos-6]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos -6;
        cpt++;
    }
    if(p->pos+17 < 64 && (p->pos+17)/8-2 == p->pos/8 &&
    (board[p->pos+17] == NULL || board[p->pos+17]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 17;
        cpt++;
    }
    if(p->pos+15 < 64 && (p->pos+15)/8-2 == p->pos/8 &&
    (board[p->pos+15] == NULL || board[p->pos+15]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 15;
        cpt++;
    }
    if(p->pos+10 < 64 && (p->pos+10)/8-1 == p->pos/8 &&
    (board[p->pos+10] == NULL || board[p->pos+10]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 10;
        cpt++;
    }
    if(p->pos+ 6 < 64 && (p->pos+6)/8-1 == p->pos/8 &&
    (board[p->pos+6] == NULL || board[p->pos+6]->isWhite != p->isWhite))
        p->possibleMoves[cpt] = p->pos + 6;
}
size_t LenPossibleMoveKnight(struct piece **board, struct piece *p)
{
    size_t res = 0;
    if(p->pos-17 > 0 && (p->pos-17)/8+2 == p->pos/8 &&
    (board[p->pos -17] == NULL || board[p->pos - 17]->isWhite != p->isWhite))
        res++;
    if(p->pos-15 > 0 && (p->pos-15)/8+2 == p->pos/8 &&
    (board[p->pos-15] == NULL || board[p->pos-15]->isWhite != p->isWhite))
        res++;
    if(p->pos-10 > 0 && (p->pos-10)/8+1 == p->pos/8 &&
    (board[p->pos-10] == NULL || board[p->pos-10]->isWhite != p->isWhite))
        res++;
    if(p->pos-6 > 0 && (p->pos-6)/8+1 == p->pos/8 &&
    (board[p->pos-6] == NULL || board[p->pos-6]->isWhite != p->isWhite))
        res++;
    if(p->pos+17 < 64 && (p->pos+17)/8-2 == p->pos/8 &&
    (board[p->pos+17] == NULL ||board[p->pos+17]->isWhite != p->isWhite))
        res++;
    if(p->pos+15 < 64 && (p->pos+15)/8-2 == p->pos/8 &&
    (board[p->pos+15] == NULL || board[p->pos+15]->isWhite != p->isWhite))
        res++;
    if(p->pos+10 < 64 && (p->pos+10)/8-1 == p->pos/8 &&
    (board[p->pos+10] == NULL || board[p->pos+10]->isWhite != p->isWhite))
        res++;
    if(p->pos+ 6 < 64 && (p->pos+6)/8-1 == p->pos/8 &&
    (board[p->pos+6] == NULL || board[p->pos+6]->isWhite != p->isWhite))
        res++;
    return res;
}

void printMove(struct piece *p)
{
    for (size_t i = 0; i < (size_t)p->nbMoves; i++)
    {
        printf("move %li = %i\n", i, p->possibleMoves[i]);
    }
}