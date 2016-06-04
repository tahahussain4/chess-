#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

int movePiece(int currentPosition[2], int nextPosition[2], char board[12][12]);

int moveRook(int currentPosition[2],char board[12][12]);

int printBoard(char board[12][12]);

#endif // INTERFACE_H_INCLUDED
