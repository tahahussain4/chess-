#include <iostream>
#include <stdio.h>

using namespace std;

int possibleMove(int currentPosition[2], int board[8][8])
{
    //This function goes through every piece and determines if the piece can be moved
    for(int i = -1; i < 2; i++)
    {
        for(int j = 0; i < 3; j++)
        {
            if(board[currentPosition[0] + i][currentPosition[1] + j] != 0)
            {
                printf("Can't move");
            }
            else
            {
                printf("You can move");
            }
        }
    }
    return 0;
}

int printBoard(int board[8][8])
{
    //Print out the board array for visualization
    for(int i = 0; i < 8; i++)
    {

        for(int j = 0; j < 8; j++)
        {
            printf("%i",board[i][j]);
        };

        printf("\n");

    };
}
