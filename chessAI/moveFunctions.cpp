#include <iostream>
#include <stdio.h>

using namespace std;

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

int moveBishop(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8])
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
    int stepNumber = rowMove;
    int rowPosition = currentPosition[0];
    int columnPosition = currentPosition[1];

    while(stepNumber != 0)
    {
        if(rowMove > 0 && columnMove > 0)
        {
            //Set the value of the square of the next piece position to the piece value
            board[rowPosition][columnPosition] = pieceID;
            rowPosition = rowPosition + 1;
            columnPosition = columnPosition + 1;
            stepNumber = stepNumber - 1;
        }
        else if(rowMove < 0 && columnMove < 0)
        {
            board[rowPosition][columnPosition] = pieceID;
            rowPosition = rowPosition - 1;
            columnPosition = columnPosition - 1;
            stepNumber = stepNumber + 1;
        }
        else if(columnMove > 0 && rowMove < 0)
        {
            board[rowPosition][columnPosition] = pieceID;
            columnPosition = columnPosition + 1;
            rowPosition = rowPosition - 1;
            stepNumber = stepNumber + 1;
        }
        else if(columnMove < 0 && rowMove > 0)
        {
            board[rowPosition][columnPosition] = pieceID;
            columnPosition = columnPosition - 1;
            rowPosition = rowPosition + 1;
            stepNumber = stepNumber - 1;
        }
    }

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

int moveQueen(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8])
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
        if(rowMove > 0 && columnMove == 0)
        {
            //Set the value of the square of the next piece position to the piece value
            board[rowPosition][currentPosition[1]] = pieceID;
            rowPosition = rowPosition + 1;
            stepNumber = stepNumber - 1;
        }
        else if(rowMove < 0 && columnMove == 0)
        {
            board[rowPosition][currentPosition[1]] = pieceID;
            rowPosition = rowPosition - 1;
            stepNumber = stepNumber + 1;
        }
        else if(columnMove > 0 && rowMove == 0)
        {
            board[currentPosition[0]][columnPosition] = pieceID;
            columnPosition = columnPosition + 1;
            stepNumber = stepNumber - 1;
        }
        else if(columnMove < 0 && rowMove == 0)
        {
            board[currentPosition[0]][columnPosition] = pieceID;
            columnPosition = columnPosition - 1;
            stepNumber = stepNumber + 1;
        }
        else if(rowMove > 0 && columnMove > 0)
        {
            //Set the value of the square of the next piece position to the piece value
            board[rowPosition][columnPosition] = pieceID;
            rowPosition = rowPosition + 1;
            columnPosition = columnPosition + 1;
            stepNumber = stepNumber - 1;
        }
        else if(rowMove < 0 && columnMove < 0)
        {
            board[rowPosition][columnPosition] = pieceID;
            rowPosition = rowPosition - 1;
            columnPosition = columnPosition - 1;
            stepNumber = stepNumber + 1;
        }
        else if(columnMove > 0 && rowMove < 0)
        {
            board[rowPosition][columnPosition] = pieceID;
            columnPosition = columnPosition + 1;
            rowPosition = rowPosition - 1;
            stepNumber = stepNumber + 1;
        }
        else if(columnMove < 0 && rowMove > 0)
        {
            board[rowPosition][columnPosition] = pieceID;
            columnPosition = columnPosition - 1;
            rowPosition = rowPosition + 1;
            stepNumber = stepNumber - 1;
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
