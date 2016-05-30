#pragma once
#ifndef CHESS_GUI_H
#define CHESS_GUI_H

//INCLUDES
//#include "resource.h"

//VARIABLE
#define Y_OFFSET 100
#define WINDOW_W 1000
#define WINDOW_L (800 + Y_OFFSET)
#define BUTTON_START_ID_MP 0x1
#define BUTTON_EXIT_ID_MP 0x2
#define widthSquare  WINDOW_W /11.0
#define homeColour 'w'     //b = black w = white
#define tileHighlightColour CreateSolidBrush(RGB(113, 183, 113))

//piece variables
#define KING 6
#define QUEEN 5
#define ROOKH 4
#define HORSE 3
#define ELEPHANT 2
#define MINION 6

class SQUARETILE {

public:
	HBRUSH background;
	HBRUSH frame;
	bool clicked = false;
	int coord[2] = { 0,0 };

private:


};

typedef struct coordHolder{
	int actualX;
	int	actualY;
	int virtualX;
	int virtualY;
} coordHolder;

typedef struct chessPiece {
	int num ;
	char colour ;
	bool atHome = true;
} chessPiece;

//FUNCTION PROTTYPES
void frontPageDraw(HWND hWnd);
void gamePageDraw(HWND hWnd, HDC hdc);

bool getTilePressed(int x, int y );
void drawRectangle(HDC hdc, int left, int top, int right, int bottom, HBRUSH back, HBRUSH frame);
bool checkMovementRules(coordHolder current, coordHolder previous, int pieceNumint , chessPiece matrixRec[8][8]);
void printPieces(HDC hdc, SQUARETILE matrixSquareTile[8][8], chessPiece matrixRec[8][8]);

void squareClickResponse(HDC hdc);
void twiceSameClickedSequence(HDC hdc, int XIndex, int YIndex);
void onceClickedSequence(HDC hdc, int XIndex, int YIndex);
void twiceDifferentClickedSequence(HDC hdc, int XIndex, int YIndex, int pXIndex, int pYIndex);
#endif