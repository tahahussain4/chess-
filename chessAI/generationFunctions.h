#ifndef GENERATIONFUNCTIONS_H_INCLUDED
#define GENERATIONFUNCTIONS_H_INCLUDED

int generateMoves(char board[12][12]);

int findMoves(char pieceID,int currentPosition[2],char board[12][12]);

int moveList(char pieceID, char List[1000][2], int currentPosition[2], int nextPosition[2]);

int checkPiece(char pieceID);

#endif // GENERATIONFUNCTIONS_H_INCLUDED
