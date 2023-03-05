#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "../Game_mechanics/game.h"
#include "testFunction.h"
#include "../Game_mechanics/movePiece.h"



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
                printf("\033[0;34m");
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



int main()
{
    struct piece **board = newBoard();
    //print_chess(board);

    


    int moved = Move(board, board[8], 24);
    printf("moved1 = %i\n", moved);
    moved = Move(board, board[0], 16);
    Move(board, board[16], 22);
    Move(board, board[12], 28);
    Move(board, board[4], 12);
    printf("moved2 = %i\n", moved);

    //moved = MovePown(board, board[19], 28);

    print_chess(board);

    freeBoard(board);
    return 1;
}