#ifndef MOVEFUNCTIONS_H_INCLUDED
#define MOVEFUNCTIONS_H_INCLUDED

//Function prototypes
int movePiece(int pieceID,int currentPosition[2], int nextPosition[2], char board[12][12]);
int moveRook(int pieceID,int currentPosition[2], int nextPosition[2], int board[12][12]);
int moveBishop(int pieceID,int currentPosition[2], int nextPosition[2], int board[12][12]);
int moveQueen(int pieceID,int currentPosition[2], int nextPosition[2], int board[12][12]);
int movePawn(int pieceID,int currentPosition[2], int nextPosition[2], int board[12][12]);
int moveKing(int pieceID,int currentPosition[2], int nextPosition[2], int board[12][12]);
int moveKnight(int pieceID,int currentPosition[2], int nextPosition[2], int board[12][12]);

#endif // MOVEFUNCTIONS_H_INCLUDED
