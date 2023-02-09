#ifndef GAME_H
#define GAME_H

struct piece 
{
    char *name;
    int hasMoved;
    int value;
};

//initializes a new piece with the given name
//returns null if wrong name
struct piece *newPiece (char* name);

#endif