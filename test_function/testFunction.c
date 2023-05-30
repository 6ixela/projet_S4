#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
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

void OnePlayer(struct piece **board, int isWhiteTurn)
{
    while(1)
    {
        print_chess(board);
        printf("Enter piece position then destinaton:\n");
        char* piecePos = calloc(3, 1);
        char* dest = calloc(3, 1);
        fgets(piecePos, 3, stdin);
        getchar();
        //si pas de piece, redemander.
        fgets(dest, 3, stdin);
        getchar();
        CalculateColorMoves(board, isWhiteTurn, 1);


        if(piecePos[0] < 'a' || piecePos[0] > 'h' || 
            piecePos[1] < '1' || piecePos[1] > '8' )
        {
            printf("incorrect character. ");
            continue;
        }
        int p1 = (piecePos[1] - '1')*8 + piecePos[0] - 'a';
        int p2 = (dest[1] - '1')*8 + dest[0] - 'a';

        printf("pos = %d to %d\n", p1,p2);

        if(!board[p1] || !(board[p1]->isWhite == isWhiteTurn))
        {
            printf("No piece on this position. ");
            continue;
        }
        if(movePiece(board, p1,p2))
        {
            break;
        }
        printf("Position not accessible. ");
    }

    int nextMoves = CalculateColorMoves(board, !isWhiteTurn, 1);
    if(nextMoves == 0)
    {
        if(isWhiteTurn)
            printf("White Won!\n");
        else
            printf("Black Won!\n");
    }
}

int main()
{
    /*
    int ok = 69;
    char r[4];
    size_t len = 0;
    while(ok)
    {
        printf("You have different mode :\n");
        printf("Enter play, test or show\n");
        read(STDIN_FILENO, r, 4);
        len = strlen(r);
        if(strncmp(r, "test", len) == 0 || strncmp(r, "play", len) == 0
        || strncmp(r, "show", len) == 0)
            ok = 0;
        else
            printf("Invalid Argument\n");
    }
    if(strncmp(r, "test", len) == 0)
    {
        char diffi[1];
        printf("Enter the difficulty of the test; easy, medium, hard (e, m, h)\n");
        read(STDIN_FILENO, diffi, 1);
        len = strlen(r);
        if(strncmp(r, "e", len) == 0)
        {
            struct piece **board = LoadFromFen("8/Q5K1/3pp3/3pk3/4rq2/2P5/2BP3B/8");
            while(1)
            {
                break;
            }
            print_chess(board);

            freeBoard(board);
        }
        else if (strncmp(r, "m", len) == 0)
        {
            struct piece **board = LoadFromFen("");
            print_chess(board);
            freeBoard(board);
        }
        else
        {
            struct piece **board = LoadFromFen("r1b1k2r/pp1n1ppp/2pbp3/3pq3/N7/PP1B4/2PBN1PP/R2Q1RK1");
            int start = -1;
            int e = -1;
            int color = 0;
            int cpt = 6;
            while(1)
            {
                print_chess(board);
                CalculateColorMoves(board, 0, 0);                
                printf("ok\n");

                CalculateColorMoves(board, 1, 1);
                printf("ok\n");

                minmaxOptiV3(board, 5, 3, color, &start, &e, INT_MIN, INT_MAX);
                color = !color;
                movePiece(board, start, e);
                cpt--;

            }

            freeBoard(board);
        }
        
        
    }
    else if(strncmp(r, "play", len) == 0)
    {
        char nb_player[1];
        printf("Enter the number of player\n");
        fflush(STDIN_FILENO);

        read(STDIN_FILENO, nb_player, 1);
        len = strlen(r);
        struct piece **board = newBoard();
        CalculateColorMoves(board, 0, 0);
        CalculateColorMoves(board, 1, 0);
        if(strncmp(r, "1", len) == 0)//Player VS IA
        {
            while (1)
            {
                print_chess(board);
                OnePlayer(board, 1);//faire une ft qui joue 1 joueur
                int s = -1;
                int e = -1;
                minmaxOptiV3(board, 5, 0, 1, &s, &e, INT_MIN, INT_MAX);
                movePiece(board, s, e);
            }
            
            
        }
        else
        {
            while (1)
            {
                turn(board, 1);
            }
        }
        
        
        freeBoard(board);
    }
    else // IA VS IA
    {
        //struct piece **board = newBoard();
        struct piece **board = newBoard();
        int start = -1;
        int end = -1;
        int color = 1;
        while(1)
        {
            CalculateColorMoves(board, 0, 0);
            CalculateColorMoves(board, 1, 0);
            print_chess(board);
            minmaxOptiV3(board, 5, color, 1, &start, &end, INT_MIN, INT_MAX);
            printf("s = %i\nend = %i\n", start, end);
            movePiece(board, start, end);
            color = !color;
        }
        
    }
    */
    

   struct piece **b = LoadFromFen("8/q5k1/3PP3/3PK3/4Rb2/2p5/2bp4/8");


    print_chessv2(b);
    int start;
    int end;
    minmaxOptiV3(b, 1, 1, 1, &start, &end, INT_MIN, INT_MAX);
    movePiece(b,start,end);
    print_chessv2(b);
    free(b);

    return 1;

}