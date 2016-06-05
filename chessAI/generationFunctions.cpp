#include <iostream>
#include <stdio.h>
#include "moveFunctions.h"

int checkPiece(char pieceID)
{
    switch(pieceID)
    {
    case 'o':
        printf("This is possible \n");
        break;
    case 'x':
        printf("Move not possible \n");
        break;
    case 'P':
        printf("Attacking a white pawn \n");
        break;
    case 'p':
        printf("Attacking a black pawn \n");
        break;
    case 'R':
        printf("Attacking a white rook \n");
        break;
    case 'r':
        printf("Attacking a black rook \n");
        break;
    case 'N':
        printf("Attacking a white knight \n");
        break;
    case 'n':
        printf("Attacking a black knight \n");
        break;
    case 'B':
        printf("Attacking a white bishop \n");
        break;
    case 'b':
        printf("Attacking a black bishop \n");
        break;
    case 'Q':
        printf("Attacking a white queen \n");
        break;
    case 'q':
        printf("Attacking a black queen \n");
        break;
    case 'A':
        printf("Attacking a white king \n");
        break;
    case 'a':
        printf("Attacking a black king \n");
        break;
    }
    return pieceID;
}

int findMoves(char pieceID,int currentPosition[2],char board[12][12])
{
    switch(pieceID)
    {
    case 'o':
        break;
    case 'x':
        break;
    case 'P':
        printf("This is a white pawn \n");
        movePawn(currentPosition,board);
        break;
    case 'p':
        printf("This is a black pawn \n");
        movePawn(currentPosition,board);
        break;
    case 'R':
        printf("This is a white rook \n");
        moveRook(currentPosition,board);
        break;
    case 'r':
        printf("This is a black rook \n");
        moveRook(currentPosition,board);
        break;
    case 'N':
        printf("This is a white knight \n");
        moveKnight(currentPosition,board);
        break;
    case 'n':
        printf("This is a black knight \n");
        moveKnight(currentPosition,board);
        break;
    case 'B':
        printf("This is a white bishop \n");
        moveBishop(currentPosition,board);
        break;
    case 'b':
        printf("This is a black bishop \n");
        moveBishop(currentPosition,board);
        break;
    case 'Q':
        printf("This is a white queen \n");
        moveQueen(currentPosition,board);
        break;
    case 'q':
        printf("This is a black queen \n");
        moveQueen(currentPosition,board);
        break;
    case 'A':
        printf("This is a white king \n");
        moveKing(currentPosition,board);
        break;
    case 'a':
        printf("This is a black king \n");
        moveKing(currentPosition,board);
        break;
    }
    return 0;
}

int generateMoves(char board[12][12])
{
    //Check each square for a piece
    for(int i = 2; i < 10; i++)
    {

        for(int j = 2; j < 10; j++)
        {
            char square = board[i][j];
            int current[2] = {i,j};
            findMoves(square,current,board);
        };

        printf("\n");

    };
}
