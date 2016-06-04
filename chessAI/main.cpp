/*
Author: Paul Le

This program is a chess AI engine that takes in a piece move and outputs the updated chess board as an array.
*/


#include <iostream>
#include <stdio.h>
#include "moveFunctions.h"
#include "interface.h"

using namespace std;

/*
Piece ID refers to a character that designates a specific piece
Pawn: P/p
Knight: N/n
Bishop: B/b
Rook: R/r
Queen; Q/q
King: A/q

Relative piece values determine which piece is worth more in order to make decisions
Pawn: 1
Knight: 3
Bishop: 3
Rook: 5
Queen; 9
King: over 9000
*/

int main()
{

    //Setting up an empty board array
    //Position is indicated by (row,column) coordinate
    //Black pieces are at the top of the array and white pieces are at the bottom of the array

    //Setting up a full board array

    char fullBoard[12][12] = {
                    {'x','x','x','x','x','x','x','x','x','x','x','x'},
                    {'x','x','x','x','x','x','x','x','x','x','x','x'},
                    {'x','x','r','n','b','q','a','b','n','r','x','x'},
                    {'x','x','p','p','p','p','p','p','p','p','x','x'},
                    {'x','x','o','o','o','o','o','o','o','o','x','x'},
                    {'x','x','o','o','o','o','o','o','o','o','x','x'},
                    {'x','x','o','o','o','o','o','o','o','o','x','x'},
                    {'x','x','o','o','o','o','o','o','o','o','x','x'},
                    {'x','x','P','P','P','P','P','P','P','P','x','x'},
                    {'x','x','R','N','B','Q','A','B','N','R','x','x'},
                    {'x','x','x','x','x','x','x','x','x','x','x','x'},
                    {'x','x','x','x','x','x','x','x','x','x','x','x'}
                    };

    printBoard(fullBoard);

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

    printBoard(fullBoard);

    return 0;
}
