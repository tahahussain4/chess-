#include <iostream>
#include <stdio.h>
#include "moveFunctions.h"
#include "interface.h"
#include "generationFunctions.h"

int main()
{

    char fullBoard[12][12] = {
                    {'x','x','x','x','x','x','x','x','x','x','x','x'},
                    {'x','x','x','x','x','x','x','x','x','x','x','x'},
                    {'x','x','r','n','b','q','a','b','n','r','x','x'},
                    {'x','x','p','p','p','p','p','p','p','p','x','x'},
                    {'x','x','o','o','o','o','o','o','o','o','x','x'},
                    {'x','x','o','o','o','o','o','o','o','o','x','x'},
                    {'x','x','o','o','o','o','o','o','o','o','x','x'},
                    {'x','x','o','o','o','o','o','o','o','o','x','x'},
                    {'x','x','P','P','P','P','P','P','P','P','x','x'},
                    {'x','x','R','N','B','Q','A','B','N','R','x','x'},
                    {'x','x','x','x','x','x','x','x','x','x','x','x'},
                    {'x','x','x','x','x','x','x','x','x','x','x','x'}
                    };

    printBoard(fullBoard);

    int x, y;

    printf("Enter the x position of the piece you would like to move: ");
    scanf("%i",&x);
    printf("Enter the y position of the piece you would like to move: ");
    scanf("%i",&y);

    int current[2] = {y + 1,x + 1};

    printf("Enter the x position of the position you would like to move to: ");
    scanf("%i",&x);
    printf("Enter the y position of the position you would like to move to: ");
    scanf("%i",&y);

    int next[2] = {y + 1,x + 1};

    generateMoves(fullBoard);

    return 0;
}
