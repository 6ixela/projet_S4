#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Game_mechanics/game.h"
#include "testFunction.h"


void print_chess(struct piece **tab)
{
    printf("_________________\n");
    for(size_t i = 0; i < 8; i++)
    {
        printf("|");
        for (size_t j = 0; j < 8; j++)
        {
            char piece = recupPiece(tab[i * 8 + j]);
            printf("%c|", piece);
        }
        printf("\n");
    }
}

char recupPiece(struct piece *p)
{
    char res = ' ';
    if(p == NULL)
        res = ' ';
    else
    {
        size_t len = strlen(p->name);
        if(strncmp(p->name, "pawn", len) == 0)
            res = 'p';
        else if (strncmp(p->name, "knight", len) == 0)
            res = 'c';
        else if (strncmp(p->name, "bishop", len) == 0)
            res = 'b';
        else if (strncmp(p->name, "rook", len) == 0)
            res = 'r';
        else if (strncmp(p->name, "queen", len) == 0)
            res = 'q';
        else if(strncmp(p->name, "king", len) == 0)
            res = 'k';
    }
    return res;
}

char *cara(char *c1)
{
    char*c2 = malloc(6);
    memcpy(c2, c1, 6);
    return c2;
}

int main()
{
    /*struct piece *p = newPiece("king");
    char c = recupPiece(p);
    printf("%c\n", c);
    free(p->name);
    free(p);*/
    struct piece **board = newBoard();
    print_chess(board);
}