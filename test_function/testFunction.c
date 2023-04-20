#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
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



int main()
{
    struct piece **board = newBoard();
    print_chess(board);

    //turn(board, 1);


    /*
    int test = evalBoard(board);
    printf("eval = %i\n", test);
    
    Move(board, board[12], 28);
    Move(board, board[52], 36);
    Move(board, board[5], 33);
    Move(board, board[3], 39);
    Move(board, board[39], 53);
    print_chess(board);
    
    //CalculateColorMoves(board, 1);
    CalculateColorMoves(board,0);
    int start = -1;
    int dest = -1;
    int retval = minmax(board, 3, 0, 1, &start, &dest);
    printf("movement found = %d-%d\n Return val = %d\n", start, dest, retval);
    MovePiece(board, board[start], dest);
    print_chess(board);

    /*printf("moved1 = %i\n", moved);
    //moved = Move(board, board[6], 21);
    //Move(board, board[16], 22);
    //Move(board, board[12], 28);
    //Move(board, board[4], 12);
    printf("moved2 = %i\n", moved);*/

    //moved = MovePown(board, board[19], 28);
    /*turn(board, 1);
    print_chess(board);*/

    CalculateColorMoves(board,0);
    CalculateColorMoves(board,1);

    
    printf("\n");
    movePiece(board, 12, 28);
    movePiece(board, 52,36);
    movePiece(board,5,33);
    movePiece(board,48,40);
    movePiece(board,11,19);

    struct piece *p = board[40];
    printf("piece pos 40 moves (%d moves): ", p->nbMoves);
    for(int i = 0; i<p->nbMoves; i++)
    {
        printf("%d, ",p->possibleMoves[i]);
    }

    int start = -1;
    int dest = -1;
    fflush(stdout);
    int retval = minmax(board, 3, 0, 1, &start, &dest);
    printf("movement found = %d-%d\n Return val = %d\n", start, dest, retval);

    
    print_chess(board);

    movePiece(board, start, dest);

    print_chess(board);



    freeBoard(board);
    return 1;
}