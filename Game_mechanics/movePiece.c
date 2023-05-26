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
    if (p->pos+isWhite < 64 && board[p->pos+isWhite] == NULL)
        res++;
    if(p->pos+isWhite-1 < 64 && (p->pos+isWhite-1)/8 == p->pos/8+(isWhite/8) &&
        board[p->pos+isWhite-1] != NULL
         && board[p->pos+isWhite-1]->isWhite != p->isWhite)
    {
        res++;
    }

    if(p->pos+isWhite+1 < 64 && (p->pos+isWhite+1)/8 == p->pos/8+(isWhite/8) && 
        board[p->pos+isWhite+1] != NULL
         && board[p->pos+isWhite+1]->isWhite != p->isWhite)
    {
        res++;
    }
    if (!p->hasMoved)
        if(p->pos+2*isWhite >= 0 && p->pos+2*isWhite < 64 && 
            board[p->pos+2*isWhite] == NULL)
            res++;    
    return res;
}
void CreatePossibleMovePawn(struct piece **board, struct piece *p)
{
    p->nbMoves = LenPossibleMovePawn(board, p);
    free(p->possibleMoves);
    p->possibleMoves = malloc(sizeof(int) * p->nbMoves);
    size_t cpt = 0;
    int isWhite = p->isWhite ? 8 : -8;

    if (p->pos+isWhite < 64 && board[p->pos+isWhite] == NULL)
    {
        p->possibleMoves[cpt] = p->pos+isWhite;
        cpt++;
    }

    if(p->pos+isWhite-1 < 64 && (p->pos+isWhite-1)/8 == p->pos/8+(isWhite/8) 
        && board[p->pos+isWhite-1] != NULL 
        && board[p->pos+isWhite-1]->isWhite != p->isWhite)
    {
        p->possibleMoves[cpt] = p->pos+isWhite-1;
        cpt++;
    }
    
    if(p->pos+isWhite+1 < 64 &&(p->pos+isWhite+1)/8 == p->pos/8+(isWhite/8) && 
        board[p->pos+isWhite+1] != NULL 
        && board[p->pos+isWhite+1]->isWhite != p->isWhite)
    {
        p->possibleMoves[cpt] = p->pos+isWhite+1;
        cpt++;
    }

    if (!p->hasMoved)
    {
        if(p->pos+2*isWhite >= 0 && p->pos+2*isWhite < 64 && 
            board[p->pos+2*isWhite] == NULL)
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
    if (strncmp(p->name, "rook", strlen(p->name)) == 0)
    {
        p->nbMoves = LenPossibleMoveTower(board, p);
        free(p->possibleMoves);
        p->possibleMoves = malloc(sizeof(int) * p->nbMoves);
    }
    
    
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
    if(p->pos - 8 >= 0 && (board[p->pos - 8] == NULL ||
    board[p->pos - 8]->isWhite != p->isWhite))
        res++;
    if((p->pos + 9)/8 == p->pos/8+1 && p->pos + 9 < 64  && (board[p->pos + 9] == NULL ||
    board[p->pos + 9]->isWhite != p->isWhite))
        res++;
    if((p->pos + 7)/8 == p->pos/8+1 && p->pos + 9 < 64  && (board[p->pos + 7] == NULL ||
    board[p->pos + 7]->isWhite != p->isWhite))
        res++;
    if(p->pos - 7 >= 0 && (p->pos - 7)/8 == p->pos/8-1 &&(board[p->pos - 7] == NULL ||
    board[p->pos - 7]->isWhite != p->isWhite))
        res++;
    if(p->pos - 9 >= 0 && (p->pos - 9)/8 == p->pos/8-1&& (board[p->pos - 9] == NULL ||
    board[p->pos - 9]->isWhite != p->isWhite))
        res++;
    if((p->pos + 1)/8 == p->pos/8 && (board[p->pos + 1] == NULL ||
    board[p->pos + 1]->isWhite != p->isWhite))
        res++;
    if(p->pos - 1 >= 0 && (p->pos - 1)/8 == p->pos/8 &&
    (board[p->pos - 1] == NULL || board[p->pos - 1]->isWhite != p->isWhite))
        res++;
    if (!p->hasMoved)
    {
        //check si rock possible
        size_t i = 1;
        while (i < 5 && board[p->pos-i]==NULL)
            i++;
        if (i == 4 && !strcmp(board[p->pos-i]->name, "rook"))
            res++;
        i=1;
        while (i < 4 && board[p->pos+i]==NULL)
        {
            i++;
        }
        if (i == 3 && !strcmp(board[p->pos+i]->name, "rook"))
            res++;
    }
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
    if(p->pos - 8 >= 0 && (board[p->pos - 8] == NULL ||
    board[p->pos - 8]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos - 8;
        cpt++;
    }
    if((p->pos + 9)/8 == p->pos/8+1 && p->pos + 9 < 64  && (board[p->pos + 9] == NULL ||
    board[p->pos + 9]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 9;
        cpt++;
    }
    if((p->pos + 7)/8 == p->pos/8+1 && p->pos + 9 < 64  && (board[p->pos + 7] == NULL ||
    board[p->pos + 7]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 7;
        cpt++;
    }
    if(p->pos - 7 >= 0 && (p->pos - 7)/8 == p->pos/8-1 &&(board[p->pos - 7] == NULL ||
    board[p->pos - 7]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos - 7;
        cpt++;
    }
    if(p->pos - 9 >= 0 && (p->pos - 9)/8 == p->pos/8-1&& (board[p->pos - 9] == NULL ||
    board[p->pos - 9]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos - 9;
        cpt++;
    }
    if((p->pos + 1)/8 == p->pos/8 && (board[p->pos + 1] == NULL ||
    board[p->pos + 1]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos + 1;
        cpt++;
    }
    if(p->pos - 1 >= 0 && (p->pos - 1)/8 == p->pos/8 &&
    (board[p->pos - 1] == NULL || board[p->pos - 1]->isWhite != p->isWhite))
    {
        p->possibleMoves[cpt] = p->pos - 1;
        cpt++;
    }
    
    if (!p->hasMoved)
    {
        //check si rock possible
        size_t i = 1;
        while (i < 5 && board[p->pos-i]==NULL)
            i++;
        if (i == 4 && !strcmp(board[p->pos-i]->name, "rook"))
        {
            p->possibleMoves[cpt] = p->pos - 2;
            cpt++;
        }
        i=1;
        while (i < 4 && board[p->pos+i]==NULL)
            i++;
        
        if (i == 3 && !strcmp(board[p->pos+i]->name, "rook"))
        {
            p->possibleMoves[cpt] = p->pos + 2;
        }  
    }
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
            CreatePossibleMoveBishop(board, p, 0);

        else if (strncmp(p->name, "rook", len) == 0)
            CreatePossibleMoveTower(board, p);

        else if (strncmp(p->name, "queen", len) == 0)
            CreatePossibleMoveQueen(board, p);
    
        else if(strncmp(p->name, "king", len) == 0)
            CreatePossibleMoveKing(board, p);
        
        size_t i = 0;

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


size_t LenPossibleMoveBishop(struct piece **board, struct piece *p)
{
    size_t res = 0;
    int i = p->pos - 9;
    int fini = 0;

    while(i>=0&&i/8+1==(i+9)/8 && !fini)
    {
        if(board[i] == NULL)
            res++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                res++;
            fini = 69;
        }
        i-=9;
    }
    i = p->pos - 7;
    fini = 0;
    while(i>=0&&i/8+1==(i+7)/8 && !fini)
    {
        if(board[i] == NULL)
            res++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                res++;
            fini = 69;
        }
        i-=7;
    }
    i = p->pos + 7;
    fini = 0;
    while(i <= 63 &&i/8-1==(i-7)/8 && !fini)
    {
        if(board[i] == NULL)
            res++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                res++;
            fini = 69;
        }
        i+=7;
    }
    i = p->pos + 9;
    fini = 0;
    while(i <= 63 &&i/8-1==(i-9)/8 && !fini)
    {
        if(board[i] == NULL)
            res++;
        else
        {
            if (board[i]->isWhite != p->isWhite)
                res++;
            fini = 69;
        }
        i+=9;
    }
    
    return res;
}
void CreatePossibleMoveBishop(struct piece **board, struct piece *p, size_t cpt)
{
    int i = p->pos - 9;
    int fini = 0;
    if (cpt == 0)
    {
        free(p->possibleMoves);
        p->nbMoves = LenPossibleMoveBishop(board, p);
        p->possibleMoves = malloc(sizeof(int) * p->nbMoves);
    }
        
    
    while(i>=0&&i/8+1==(i+9)/8 && !fini)
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
        i-=9;
    }
    i = p->pos - 7;
    fini = 0;
    while(i>=0&&i/8+1== (i+7)/8 && !fini)
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
        i-=7;
    }
    i = p->pos + 7;
    fini = 0;
    while(i <= 63 &&i/8-1==(i-7)/8 && !fini)
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
        i+=7;
    }
    i = p->pos + 9;
    fini = 0;
    while(i <= 63 &&i/8-1==(i-9)/8 && !fini)
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
        i+=9;
    }
}
void printMove(struct piece *p)
{
    for (size_t i = 0; (int)i < p->nbMoves; i++)
    {
        printf("move %ld = %i\n", i, p->possibleMoves[i]);
    }
}

void CreatePossibleMoveQueen(struct piece **board, struct piece *p)
{
    size_t i1 = LenPossibleMoveBishop(board, p);
    size_t i2 = LenPossibleMoveTower(board, p);
    free(p->possibleMoves);
    p->nbMoves = i1 + i2;
    p->possibleMoves = malloc(sizeof(int) * p->nbMoves);

    CreatePossibleMoveTower(board, p);
    CreatePossibleMoveBishop(board, p, i2);
}