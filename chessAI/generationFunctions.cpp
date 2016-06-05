#include <iostream>
#include <stdio.h>

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
        printf("This is a white pawn \n");
        break;
    case 'p':
        printf("This is a black pawn \n");
        break;
    case 'R':
        printf("This is a white rook \n");
        break;
    case 'r':
        printf("This is a black rook \n");
        break;
    case 'N':
        printf("This is a white knight \n");
        break;
    case 'n':
        printf("This is a black knight \n");
        break;
    case 'B':
        printf("This is a white bishop \n");
        break;
    case 'b':
        printf("This is a black bishop \n");
        break;
    case 'Q':
        printf("This is a white queen \n");
        break;
    case 'q':
        printf("This is a black queen \n");
        break;
    case 'A':
        printf("This is a white king \n");
        break;
    case 'a':
        printf("This is a black king \n");
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
            checkPiece(square);
        };

        printf("\n");

    };
}
