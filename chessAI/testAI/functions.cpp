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

int moveRook(int currentPosition[2],char board[12][12])
{
    int top = true;
    int bottom = true;
    int left = true;
    int right = true;
    int n = 1;
    while(top || bottom || left || right)
    {
        if(top)
        {
            if(board[currentPosition[0] + n][currentPosition[1]] == 'o')
            {
                printf("This is possible (t) \n");
            }
            else
            {
                char square = board[currentPosition[0] + n][currentPosition[1]];
                switch(square)
                {
                case 'x':
                    printf("Move not possible (t) \n");
                    break;
                case 'P':
                    printf("This is a pawn (t) \n");
                    break;
                }
                top = false;
            }
        }

        if(bottom)
        {
            if(board[currentPosition[0] - n][currentPosition[1]] == 'o')
            {
                printf("This is possible (b) \n");
            }
            else
            {
                char square = board[currentPosition[0] - n][currentPosition[1]];
                switch(square)
                {
                case 'x':
                    printf("Move not possible (b) \n");
                    break;
                case 'p':
                    printf("This is a pawn (b) \n");
                    break;
                }
                bottom = false;
            }
        }

        if(left)
        {
            if(board[currentPosition[0]][currentPosition[1] - n] == 'o')
            {
                printf("This is possible (l) \n");
            }
            else
            {
                char square = board[currentPosition[0]][currentPosition[1] - n];
                switch(square)
                {
                case 'x':
                    printf("Move not possible (l) \n");
                    break;
                case 'p':
                    printf("This is a pawn (l) \n");
                    break;
                }
                left = false;
            }
        }

        if(right)
        {
            if(board[currentPosition[0]][currentPosition[1] + n] == 'o')
            {
                printf("This is possible (r) \n");
            }
            else
            {
                char square = board[currentPosition[0]][currentPosition[1] + n];
                switch(square)
                {
                case 'x':
                    printf("Move not possible (r) \n");
                    break;
                case 'p':
                    printf("This is a pawn (r) \n");
                    break;
                }
                right = false;
            }
        }

        n = n + 1;

    }
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
