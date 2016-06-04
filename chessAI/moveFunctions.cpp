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

int moveBishop(int currentPosition[2],char board[12][12])
{
    int top_right = true;
    int top_left = true;
    int bottom_right = true;
    int bottom_left = true;
    int n = 1;
    while(top_right || bottom_left || top_left || bottom_right)
    {
        if(top_right)
        {
            if(board[currentPosition[0] + n][currentPosition[1] + n] == 'o')
            {
                printf("This is possible (tr) \n");
            }
            else
            {
                char square = board[currentPosition[0] + n][currentPosition[1] + n];
                switch(square)
                {
                case 'x':
                    printf("Move not possible (tr) \n");
                    break;
                case 'P':
                    printf("This is a pawn (tr) \n");
                    break;
                }
                top_right = false;
            }
        }

        if(bottom_right)
        {
            if(board[currentPosition[0] - n][currentPosition[1] + n] == 'o')
            {
                printf("This is possible (br) \n");
            }
            else
            {
                char square = board[currentPosition[0] - n][currentPosition[1] + n];
                switch(square)
                {
                case 'x':
                    printf("Move not possible (br) \n");
                    break;
                case 'p':
                    printf("This is a pawn (br) \n");
                    break;
                }
                bottom_right = false;
            }
        }

        if(top_left)
        {
            if(board[currentPosition[0] + n][currentPosition[1] - n] == 'o')
            {
                printf("This is possible (tl) \n");
            }
            else
            {
                char square = board[currentPosition[0] + n][currentPosition[1] - n];
                switch(square)
                {
                case 'x':
                    printf("Move not possible (tl) \n");
                    break;
                case 'p':
                    printf("This is a pawn (tl) \n");
                    break;
                }
                top_left = false;
            }
        }

        if(bottom_left)
        {
            if(board[currentPosition[0] - n][currentPosition[1] - n] == 'o')
            {
                printf("This is possible (bl) \n");
            }
            else
            {
                char square = board[currentPosition[0] - n][currentPosition[1] - n];
                switch(square)
                {
                case 'x':
                    printf("Move not possible (bl) \n");
                    break;
                case 'p':
                    printf("This is a pawn (bl) \n");
                    break;
                }
                bottom_left = false;
            }
        }

        n = n + 1;

    }
    return 0;
}
