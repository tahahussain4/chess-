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

int movePiece(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8])
{

    //This function moves a piece and updates the board array
    //It takes in the current position of the piece and the final position of the piece, and updates the board array to reflect that move

    //These variables store how much the piece was moved in the row and column directions
    int rowMove;
    int columnMove;

    //Calculate how far the piece was moved in the row and column direction
    rowMove = nextPosition[0] - currentPosition[0];
    columnMove = nextPosition[1] - currentPosition[1];

    //Set the value of the square of the current piece position to zero
    board[currentPosition[0]][currentPosition[1]] = 0;
    //Set the value of the square of the next piece position to the piece value
    board[currentPosition[0] + rowMove][currentPosition[1] + columnMove] = pieceID;

    return 0;

}

int moveRook(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8])
{

    //This function moves a piece and updates the board array
    //It takes in the current position of the piece and the final position of the piece, and updates the board array to reflect that move

    //These variables store how much the piece was moved in the row and column directions
    int rowMove;
    int columnMove;

    //Calculate how far the piece was moved in the row and column direction
    rowMove = nextPosition[0] - currentPosition[0];
    columnMove = nextPosition[1] - currentPosition[1];

    //Set the value of the square of the current piece position to zero
    board[currentPosition[0]][currentPosition[1]] = 0;

    //This for loop iterates through all the adjacent square steps taken in order to reach the next position, and performs some kind of logic for each square

    //This keeps track of total number of steps that can be taken, if rowMove is not zero then columnMove is zero, and vice versa
    int stepNumber = rowMove + columnMove;
    int rowPosition = currentPosition[0];
    int columnPosition = currentPosition[1];

    while(stepNumber != 0)
    {
        if(rowMove > 0)
        {
            //Set the value of the square of the next piece position to the piece value
            board[rowPosition][currentPosition[1]] = pieceID;
            rowPosition = rowPosition + 1;
            stepNumber = stepNumber - 1;
        }
        else if(rowMove < 0)
        {
            board[rowPosition][currentPosition[1]] = pieceID;
            rowPosition = rowPosition - 1;
            stepNumber = stepNumber + 1;
        }
        else if(columnMove > 0)
        {
            board[currentPosition[0]][columnPosition] = pieceID;
            columnPosition = columnPosition + 1;
            stepNumber = stepNumber - 1;
        }
        else if(columnMove < 0)
        {
            board[currentPosition[0]][columnPosition] = pieceID;
            columnPosition = columnPosition - 1;
            stepNumber = stepNumber + 1;
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
