#ifndef MOVEFUNCTIONS_H_INCLUDED
#define MOVEFUNCTIONS_H_INCLUDED

//Function prototypes
int movePiece(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int moveRook(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int moveBishop(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int moveQueen(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int movePawn(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int moveKing(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int moveKnight(int pieceID,int currentPosition[2], int nextPosition[2], int board[8][8]);
int printBoard(int board[8][8]);

#endif // MOVEFUNCTIONS_H_INCLUDED
