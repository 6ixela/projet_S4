#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "movePiece.h"
#include "minMax.h"
#include "../test_function/testFunction.h"


struct piece *newPiece(char *name)
{
    struct piece *res =  malloc(sizeof(struct piece));
    size_t len = strlen(name) + 1;
    if(strncmp(name, "pawn", len) == 0)
        res->value = 100;
    else if (strncmp(name, "knight", len) == 0)
        res->value = 300;
    else if (strncmp(name, "bishop", len) == 0)
        res->value = 300;
    else if (strncmp(name, "rook", len) == 0)
        res->value = 500;
    else if (strncmp(name, "queen", len) == 0)
        res->value = 900;
    else if (strncmp(name, "king", len) == 0)
        res->value = 2000;
    else
    {
        free(res);
        res = NULL;
    }
    if(res)
    {
        res->hasMoved = 0;
        res->isWhite = 0;
        res->nbMoves = 0;
        res->name = malloc(len);
        res->possibleMoves = malloc(0);
        memcpy(res->name, name, len);
    }
    return res;
}

void freePiece(struct piece *p)
{
    free(p->name);

    free(p->possibleMoves);
    
    free(p);
}

struct piece **newBoard()
{
    //malloc board size: 64 pointers
    struct piece **board = malloc(sizeof(struct piece*) * 64);
    for (int i = 0; i<64; i++)
    {
        board[i] = NULL;
    }

    //list to place pieces
    char piecesNames[][10] = {"rook", "knight", "bishop", "queen", "king",
    "bishop", "knight", "rook"};

    for(int x = 0; x<8; x++)
    {
        int posW1 = 8+x;
        int posW2 = x;
        int posB1 = 48+x;
        int posB2 = 56+x;
        //place pawns
        placePiece(board, "pawn", posW1);
        placePiece(board, "pawn", posB1);
        board[posW1]->isWhite = 1;

        //place others
        placePiece(board, piecesNames[x], posW2);
        placePiece(board, piecesNames[x], posB2);
        board[posW2]->isWhite = 1;
    }

    return board;
}

void freeBoard(struct piece **board)
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            struct piece *p = board[i * 8 + j];
            if (p != NULL)
            {
                freePiece(p);
            }   
        }   
    }
    free(board);
}

int placePiece(struct piece **board, char* name, int pos)
{
    int res = 0;
    if(pos < 0 || pos > 63)
    {
        printf("place_piece: Error in position\n");
        res = -1;
    }
    else if(board[pos] != NULL)
    {
        printf("place_piece: A piece is already there!\n");
        res = 1;
    }
    else
    {
        board[pos] = newPiece(name);
        board[pos]->pos = pos;
    }
    return res;
}

int movePiece(struct piece **board, int pos, int dest)
{
    return __movePiece(board, pos, dest, 1);
}

//used to be able to not filter moves. else use movePiece
int __movePiece(struct piece **board, int pos, int dest, int filterMoves)
{
    struct piece *piece = board[pos];
    int res = 0;
    if(piece != NULL)
    {
        int isPossible = 0;
        int i =0;
        while(i<piece->nbMoves && !isPossible)
        {
            isPossible = piece->possibleMoves[i] == dest;
            i++;
        }
        if(isPossible)
        {
            if(board[dest] != NULL)
            {
                //eats the piece on the position
                freePiece(board[dest]);
            }
            
            board[dest] = piece;
            board[pos] = NULL;
            piece->hasMoved = 1;
            piece->pos = dest;
        }
        res = isPossible;
    }
    CalculateColorMoves(board,!(piece->isWhite), filterMoves);
    return res;
}

void turn(struct piece **board, int isWhiteTurn)
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

    printf("line 183\n");
    int nextMoves = CalculateColorMoves(board, !isWhiteTurn, 1);
    printf("line 185\n");
    if(nextMoves == 0)
    {
        if(isWhiteTurn)
            printf("White Won!\n");
        else
            printf("Black Won!\n");
    }
    else
    {
        //calls again for next turn from other player
        turn(board, !isWhiteTurn);
    }
}

int CalculateColorMoves(struct piece** board, int isWhite, int filterMoves)
{
    int res = 0;
    for(size_t i = 0; i<63; i++)
    {
        struct piece *p = board[i];
        if(p != NULL && p->isWhite == isWhite)
        {
            //printf("doing %s at pos %d\n", p->name, i);
            //fflush(stdout);
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

            if(filterMoves)
                FilterMoves(board, p);
            res+= p->nbMoves;
        }
    }
    return res;
}

void FilterMoves(struct piece **board, struct piece *p)
{
    int removed = 0;
    for (int i = 0; i<p->nbMoves; i++)
    {
        if(TestCheckmate(board,p,p->possibleMoves[i]))
        {
            p->possibleMoves[i] = -1;
            removed++;
        }
    }
    int* newmoves = malloc(sizeof(int) * (p->nbMoves-removed));
    int j = 0;
    for (int i = 0; i<p->nbMoves; i++)
    {
        if(p->possibleMoves[i] >= 0)
        {
            newmoves[j] = p->possibleMoves[i];
            j++;
        }
    }
    p->nbMoves -= removed;
    free(p->possibleMoves);
    p->possibleMoves = newmoves;
}

int __TestCheckmate(struct piece **board, int isWhite)
{
    for(size_t i = 0; i<63; i++)
    {
        struct piece *p = board[i];
        if(p != NULL && p->isWhite != isWhite)
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
            
            for(int k = 0; k<p->nbMoves;k++)
            {
                struct piece *p2 = board[p->possibleMoves[k]];
                if(p2 && strncmp(p2->name, "king", strlen(p2->name)) == 0)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int TestCheckmate(struct piece **board ,struct piece *piece, int dest)
{
    struct piece **copy = deepCopy(board);
    __movePiece(copy, piece->pos, dest, 0);
    int res = __TestCheckmate(copy, piece->isWhite);
    freeBoard(copy);
    return res;
}

int isCheck(struct piece **board, int isWhite)
{
    CalculateColorMoves(board, !isWhite, 0);
    for(size_t i = 0; i<63; i++)
    {
        struct piece *p = board[i];
        if(p!=NULL && p->isWhite != isWhite)
        {
            for(int k = 0; k<p->nbMoves; k++)
            {
                struct piece *p2 = board[p->possibleMoves[k]];
                if(p2 != NULL && strncmp(p2->name,"king", strlen(p2->name))==0)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}