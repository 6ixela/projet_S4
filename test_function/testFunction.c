#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <err.h>
#include <time.h>
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
int who_won(struct piece **board)
{
    int res = 0;
    for(size_t i = 0; i<64; i++)
    {
        struct piece *p = board[i];
        if(p)
            if(!strcmp(p->name, "king"))
                res += p->isWhite ? 1 : -1;
    }
    return res;
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


void allMove(struct piece **board)
{
    for (size_t i = 0; i < 64; i++)
    {
        struct piece *p = board[i];
        if(p)
            p->hasMoved = 1;
    }
    
}

/*int main(int argc, char* argv[])
{
    if(strncmp(argv[1], "test", 4) == 0)
    {
        if (argc != 4)
            errx(3, "Invalid Argument");

        int prof = *argv[2] - '0';
        printf("argv[2] = %d\n", prof);
        if(strncmp(argv[3], "easy", 4) == 0)
        {
            struct piece **board5 = LoadFromFen("7k/1q4pp/5p2/2p5/N7/1P1r4/P7/KR4B1");
            allMove(board5);
            int cpt = 0;
            int s = -1;
            int e = -1;
            int color = 0;
            while (cpt < 5)
            {
                print_chess(board5);
                CalculateColorMoves(board5, 1, 0);
                CalculateColorMoves(board5, 0, 0);
                
                minmaxOptiV3(board5, prof, color, 1, &s, &e, INT_MIN, INT_MAX);
                movePiece(board5, s, e);
                color = !color;
                cpt++;
            }
            
            freeBoard(board5);
        }
        else if (strncmp(argv[3], "medium", 6) == 0)
        {
            struct piece **board = LoadFromFen("K1B5/8/1Q6/8/8/n6r/1R4n1/4r2k");
            allMove(board);
            int cpt = 0;
            int s = -1;
            int e = -1;
            int color = 1;
            while (cpt < 10)
            {
                print_chess(board);
                
                CalculateColorMoves(board, 1, 0);
                CalculateColorMoves(board, 0, 0);

                minmaxOptiV3(board, prof, color, 1, &s, &e, INT_MIN, INT_MAX);
                movePiece(board, s, e);
                color = !color;
                cpt++;
            }
            freeBoard(board);
        }
        else
        {
            struct piece **board5 = LoadFromFen("kb6/b1r1n3/7p/8/8/4N3/1BR5/KR6");
            allMove(board5);
            int cpt = 0;
            int s = -1;
            int e = -1;
            int color = 0;
            while (cpt < 5)
            {
                print_chess(board5);
                CalculateColorMoves(board5, 1, 0);
                CalculateColorMoves(board5, 0, 0);
                minmaxOptiV3(board5, prof, color, 1, &s, &e, INT_MIN, INT_MAX);

                movePiece(board5, s, e);
                color = !color;
                cpt++;

            }
            
            freeBoard(board5);
        }
        
        
    }
    else if(strncmp(argv[1], "play", 4) == 0)
    {
        if (argc != 3)
            errx(3, "Invalid Argument");
        int nb_player = *argv[2]-'0';
        struct piece **board = newBoard();
        CalculateColorMoves(board, 0, 0);
        CalculateColorMoves(board, 1, 0);
        if(nb_player == 1)//Player VS IA
        {
            while (!who_won(board))
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
            while (!who_won(board))
            {
                turn(board, 1);
            }
        }
        
        
        freeBoard(board);
    }
    else // IA VS IA
    {
        if(argc != 3)
            errx(3, "Invalid Argument");
        int prof = *argv[2]-'0';
        struct piece **board = newBoard();
        int start = -1;
        int end = -1;
        int color = 1;
        while(!who_won(board))
        {
            CalculateColorMoves(board, 0, 0);
            CalculateColorMoves(board, 1, 0);
            print_chess(board);
            minmaxOptiV3(board, prof, color, 1, &start, &end, INT_MIN, INT_MAX);
            printf("s = %i\nend = %i\n", start, end);
            movePiece(board, start, end);
            color = !color;
        }
        
    }
    return 0;
}*/
