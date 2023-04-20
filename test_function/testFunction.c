#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include "../Game_mechanics/game.h"
#include "testFunction.h"
#include "../Game_mechanics/movePiece.h"
#include "../Game_mechanics/minMax.h"



void print_chess(struct piece **tab)
{
    printf("_________________\n");
    for(size_t i = 0; i < 8; i++)
    {
        printf("|");
        for (size_t j = 0; j < 8; j++)
        {
            char *piece = recupPiece(tab[i * 8 + j]);
            if (tab[i * 8 + j] != NULL && !tab[i * 8 + j]->isWhite)
            {
                printf("\033[0;32m");
                printf("%s", piece);
                printf("\033[0m");
                printf("|");
            }
            else
                printf("%s|", piece);
        }
        printf("\n");
    }
    printf("_________________\n");
}


char *recupPiece(struct piece *p)
{
    char *res = " ";
    if(p == NULL)
        res = " ";
    else
    {
        size_t len = strlen(p->name);
        if(strncmp(p->name, "pawn", len) == 0)
            res = "♙";
        else if (strncmp(p->name, "knight", len) == 0)
            res = "♘";
        else if (strncmp(p->name, "bishop", len) == 0)
            res = "♗";
        else if (strncmp(p->name, "rook", len) == 0)
            res = "♖";
        else if (strncmp(p->name, "queen", len) == 0)
            res = "♕";
        else if(strncmp(p->name, "king", len) == 0)
            res = "♔";
    }
    return res;
}

char *cara(char *c1)
{
    printf("---------------------\n");
    int len = strlen(c1) + 1;
    char *c2 = malloc(len);
    printf("---------------------\n");

    memcpy(c2, c1, len);
    printf("---------------------\n");
    printf("---------------------\n");
    return c2;
}

char *recupPiecev2(struct piece *p, int pos)
{
    char *res = malloc(3);
    if(p == NULL)
        snprintf(res, 3, "%02d", pos);
    else
    {
        size_t len = strlen(p->name);
        if(strncmp(p->name, "pawn", len) == 0)
            res = "♙ ";
        else if (strncmp(p->name, "knight", len) == 0)
            res = "♘ ";
        else if (strncmp(p->name, "bishop", len) == 0)
            res = "♗ ";
        else if (strncmp(p->name, "rook", len) == 0)
            res = "♖ ";
        else if (strncmp(p->name, "queen", len) == 0)
            res = "♕ ";
        else if(strncmp(p->name, "king", len) == 0)
            res = "♔ ";
    }
    return res;
}
void print_chessv2(struct piece **tab)
{
    printf("_________________\n");
    for(size_t i = 0; i < 8; i++)
    {
        printf("|");
        for (size_t j = 0; j < 8; j++)
        {
            char *piece = recupPiecev2(tab[i * 8 + j], i * 8 + j);
            if (tab[i * 8 + j] != NULL && !tab[i * 8 + j]->isWhite)
            {
                printf("\033[0;32m");
                printf("%s", piece);
                printf("\033[0m");
                printf("|");
            }
            else
                printf("%s|", piece);
        }
        printf("\n");
    }
    printf("_________________\n");
}


struct piece **LoadFromFen(char* fen)
{
    struct piece **board = malloc(sizeof(struct piece*) * 64);
    for (int i = 0; i<64; i++)
    {
        board[i] = NULL;
    }

    int i = 0;
    while(*fen != 0 && *fen != ' ')
    {
        char c = *fen;
        int isWhite = 1;
        if(isupper(c))
        {
            isWhite = 0;
            c = tolower(c);
        }
        if(c == 'r')
            placePiece(board, "rook", i);
        else if (c == 'n')
            placePiece(board, "knight", i);
        else if (c == 'b')
            placePiece(board, "bishop", i);
        else if (c == 'q')
            placePiece(board, "queen", i);
        else if (c == 'k')
            placePiece(board, "king", i);
        else if (c == 'p')
            placePiece(board, "pawn", i);
        else if (c >= '1' && c <= '8')
            i+= *fen - '0';
        if(c=='r'||c=='n'||c=='b'||c=='q'||c=='k'||c=='p')
        {
            if(isWhite)
                board[i]->isWhite = 1;
            i++;
        }
        fen++;
    }
    return board;
}

int testAllMoves(struct piece **board, int depth, int isWhite)
{
    if(depth == 0)
        return 1;
    
    int nbpos = 0;
    for(int i = 0; i<64; i++)
    {
        struct piece *p = board[i];
        if(p != NULL && p->isWhite == isWhite)
        {
            for(int k = 0; k<p->nbMoves; k++)
            {
                struct piece **copy = deepCopy(board);
                movePiece(copy, p->pos, p->possibleMoves[k]);
                nbpos += testAllMoves(copy,depth-1, !isWhite);
                freeBoard(copy);
            }
        }
    }
    return nbpos;
}

int main()
{
    struct piece **b1 = LoadFromFen("rn1q1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R");
    print_chessv2(b1);

    struct piece **b2 = LoadFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    print_chessv2(b2);

    CalculateColorMoves(b2,0,1);
    CalculateColorMoves(b2,1,1);

    for(int i = 1;i<4;i++)
    {
        int nbmoves = testAllMoves(b2, i, 1);

        printf("nbmoves for board 2 at depth %d = %d\n", i,nbmoves);
    }


    freeBoard(b1);
    freeBoard(b2);
    return 1;
}