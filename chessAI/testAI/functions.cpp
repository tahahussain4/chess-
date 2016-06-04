#include <iostream>
#include <stdio.h>

int movePiece(int currentPosition[2], int nextPosition[2], char board[12][12])
{
    int rowMove;
    int columnMove;

    rowMove = nextPosition[0] - currentPosition[0];
    columnMove = nextPosition[1] - currentPosition[1];

    char pieceID = board[currentPosition[0]][currentPosition[1]];

    board[currentPosition[0]][currentPosition[1]] = 'o';

    board[currentPosition[0] + rowMove][currentPosition[1] + columnMove] = pieceID;

    return 0;

}

int printBoard(char board[12][12])
{
    for(int i = 0; i < 12; i++)
    {

        for(int j = 0; j < 12; j++)
        {
            printf("%c",board[i][j]);
        };

        printf("\n");

    };
}
