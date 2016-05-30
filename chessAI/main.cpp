/*
Author: Paul Le

This program is a chess AI engine that takes in a piece move and outputs the updated chess board as an array.
*/


#include <iostream>
#include <stdio.h>

using namespace std;

/*
Piece ID refers to a value that designates a specific piece, and should not be confused with the relative value of the piece
Pawn: 1
Knight: 2
Bishop: 3
Rook: 4
Queen; 5
King: 6

Relative piece values determine which piece is worth more in order to make decisions
Pawn: 1
Knight: 3
Bishop: 3
Rook: 5
Queen; 9
King: over 9000
*/

//Function prototypes
int movePiece(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int moveRook(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int printBoard(int board[8][8]);

int main()
{

    //Setting up an empty board array
    //Position is indicated by (row,column) coordinate
    //Black pieces are at the top of the array and white pieces are at the bottom of the array

    int emptyBoard[8][8] = {
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}
                    };

    //Setting up a full board array

    int fullBoard[8][8] = {
                    {4,2,3,5,6,3,2,4},
                    {1,1,1,1,1,1,1,1},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {1,1,1,1,1,1,1,1},
                    {4,2,3,5,6,3,2,4}
                    };

    //Take input variables

    int x, y;

    printf("Enter the x position of the piece you would like to move: ");
    scanf("%i",&x);
    printf("Enter the y position of the piece you would like to move: ");
    scanf("%i",&y);

    int current[2] = {y - 1,x - 1};

    printf("Enter the x position of the position you would like to move to: ");
    scanf("%i",&x);
    printf("Enter the y position of the position you would like to move to: ");
    scanf("%i",&y);

    int next[2] = {y - 1,x - 1};

    moveRook(3,current,next,fullBoard);

    printBoard(fullBoard);

    return 0;
}
