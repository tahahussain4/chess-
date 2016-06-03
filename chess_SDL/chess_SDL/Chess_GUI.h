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

//colour for the individual pieces
#define darkColour CreateSolidBrush(RGB(0, 0, 0)) 
#define lightColour CreateSolidBrush(RGB(255, 255, 255))
#define EMPTYSPACES	CreateSolidBrush(RGB(255, 229, 204))
#define ENEMYCOLOUR CreateSolidBrush(RGB(255, 178, 102))
#define CASTLECOLOUR CreateSolidBrush(RGB(178, 102, 255))
#define TILECOLOURONE COLOR_MENUTEXT
#define TILECOLOURTWO COLOR_INFOTEXT

//piece variables
#define KING 1
#define QUEEN 2
#define ROOKH 3
#define HORSE 4
#define ELEPHANT 5
#define MINION 6
#define EMPTY 0


//postion for chesspiece postions
#define xPosition 0
#define yPosition 1

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
	int pos[2] = { 0,0 };
} chessPiece;

//FUNCTION PROTTYPES
void frontPageDraw(HWND hWnd);
void gamePageDraw(HWND hWnd, HDC hdc);
void drawRectangle(HDC hdc, int posX, int posY, HBRUSH back, HBRUSH frame);
void drawSmallRectangle(HDC hdc, int left, int top, int right, int bottom, HBRUSH back, HBRUSH frame);
bool getTilePressed(int x, int y );
//coordHolder getTileHover(int x, int y);

void squareClickResponse(HDC hdc);
//void squareHoverResp(HDC hdc);


#endif