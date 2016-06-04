#include <iostream>
#include <stdio.h>

using namespace std;

int possibleMove(int currentPosition[2], int board[12][12])
{
    //This function goes through every piece and determines if the piece can be moved
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; i < 2; j++)
        {
            if(board[currentPosition[0] + i][currentPosition[1] + j] != 0)
            {
                int square = board[currentPosition[0] + i][currentPosition[1] + j];
                printf("Can't move %i \n", square);
            }
            else if(board[currentPosition[0] + i][currentPosition[1] + j] == 0)
            {
                int square = board[currentPosition[0] + i][currentPosition[1] + j];
                printf("You can move %i \n",square);
            }
        };
    }
    return 0;
}

int printBoard(char board[12][12])
{
    //Print out the board array for visualization
    for(int i = 0; i < 12; i++)
    {

        for(int j = 0; j < 12; j++)
        {
            printf("%c",board[i][j]);
        };

        printf("\n");

    };
}
