#include <iostream>
#include <stdio.h>

using namespace std;

//Piece values refers to a value that designates a specific piece, and should not be confused with the relative value of the piece
//Pawn: 1
//Knight: 2
//Bishop: 3
//Rook: 4
//Queen; 5
//King: 6

int movePiece(int pieceValue,int currentPosition[2], int nextPosition[2], int board[8][8])
{
    //These variables store how much the piece was moved in the row and column directions
    int rowMove;
    int columnMove;

    //Calculate how far the piece was moved in the row and column direction
    rowMove = nextPosition[0] - currentPosition[0];
    columnMove = nextPosition[1] - currentPosition[1];

    //Set the value of the square of the current piece position to zero
    board[currentPosition[0]][currentPosition[1]] = 0;
    //Set the value of the square of the next piece position to the piece value
    board[currentPosition[0]][currentPosition[1]] = pieceValue;

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

    //int current[2] = {5,5};
    //int next[2] = {2,2};
    //movePiece(3,current,next,board);

    return 0;
}
