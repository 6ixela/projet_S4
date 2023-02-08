#include <stdio.h>


void print_chess(char **tab)
{
    printf("_____________________________\n");
    for(size_t i = 0; i < 8; i++)
    {
        printf("|");
        for (size_t j = 0; j < 8; j++)
        {
            printf("%c|");
        }
        printf("\n_____________________________\n");
    }
}