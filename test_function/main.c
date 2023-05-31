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

int main(int argc, char* argv[])
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
}
