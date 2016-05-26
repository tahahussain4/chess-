#include <iostream>
#include <stdio.h>

using namespace std;

int movePiece(int currentPosition[2], int nextPosition[2])
{
    int rowMove;
    int columnMove;

    rowMove = nextPosition[0] - currentPosition[0];
    columnMove = nextPosition[1] - currentPosition[1];
}

int main()
{

    //Setting up the board array

    int board[8][8] = {
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}
                    };

    return 0;
}
