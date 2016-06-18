#ifndef GENERATIONFUNCTIONS_H_INCLUDED
#define GENERATIONFUNCTIONS_H_INCLUDED

int generateMoves(char board[12][12]);

int findMoves(char pieceID,int currentPosition[2],char board[12][12]);

int moveList(char pieceID, int List[1000][6], int cx, int cy, int nx, int ny);

int checkPiece(char pieceID);

#endif // GENERATIONFUNCTIONS_H_INCLUDED
