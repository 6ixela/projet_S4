#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

struct piece *newPiece(char *name)
{
    struct piece *res =  malloc(sizeof(struct piece));
    size_t len = strlen(name);
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
    else if (strncmp(name, "king", len) != 0)
    {
        free(res);
        res = NULL;
    }
    if(res)
    {
        res->hasMoved = 0;
        res->name = malloc(len);
        memcpy(res->name, name, len+1);
    }
    return res;
}