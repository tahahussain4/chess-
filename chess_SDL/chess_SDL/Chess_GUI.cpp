//INLCUDES and DEFINES
#include "stdafx.h"
#include "chess_GUI.h"
#include "math.h"

//FUNCTION prototyprd
bool pathCheck(float diffX, float diffY, int directionX, int directionY, int tempX, int tempY, chessPiece matrixRec[8][8]);
//GLOBAL variables Front page
HWND				hwndButton, hwndButton2;
bool				firstTimeGameDisp = true;
bool				clickedOnce = false;        //somethig has been clicked 
coordHolder			squareClickedCoords = { 0,0,0,0 };  //stores the rectanlge coordinates(x,y) and tile index(x,y)
coordHolder			prevClicked = { 0,0,0,0 };			//dtores prevviously clicked coordinates
chessPiece			matrixPieces[8][8];			//matrix to store chess piece and thier colour
SQUARETILE			matrixSquareTile[8][8];   //to store the properties of each tile
bool				twoPlayers = true;
char				turnColour = 'w';       //starts out with white


//initalize intial chessp piece positions in  matrix
void piecesInit() {
	//two avaible colours which change depnding on home color
	char colour[2];

	if (homeColour == 'b') {
		colour[0] = 'w';
		colour[1] = 'b';

	}
	else if(homeColour =='w'){
		colour[0] = 'b';

		colour[1] = 'w';

	}


	chessPiece empty;
	chessPiece elephantA, horseA, minionA, rookhA, queenA, kingA,
		elephantH, horseH, minionH, rookhH, queenH, kingH;

	//fill allw ith empty
	empty.num = 1;
	for (int i = 0; i < 8; i++) {
		for (int y = 0; i < 8; i++) {
			matrixPieces[i][y].num = 0;
		}
	}

	//AWAY--------
	//minions
	minionA.num = 6; minionA.colour = colour[0];
	//elephant
	elephantA.num = 5; elephantA.colour = colour[0];

	//horse
	horseA.num = 4; horseA.colour = colour[0];

	//rookh
	rookhA.num = 3; rookhA.colour = colour[0];

	//queen
	queenA.num = 2; queenA.colour = colour[0];

	//king
	kingA.num = 1; kingA.colour = colour[0];

	//HOME---------

	//minions
	minionH.num = 6; minionH.colour = colour[1];
	//elephHnt
	elephantH.num = 5; elephantH.colour = colour[1];

	//horse
	horseH.num = 4; horseH.colour = colour[1];

	//rookh
	rookhH.num = 3; rookhH.colour = colour[1];

	//queen
	queenH.num = 2; queenH.colour = colour[1];

	//king
	kingH.num = 1; kingH.colour = colour[1];

	//fill array HOME and AWAY -------------
	for (int i = 0; i < 8; i++) {
		matrixPieces[1][i] = minionA;
		matrixPieces[6][i] = minionH;
	}
	//elephant
	matrixPieces[0][0] = elephantA; matrixPieces[0][7] = elephantA;
	matrixPieces[7][0] = elephantH; matrixPieces[7][7] = elephantH;
	//horse
	matrixPieces[0][1] = horseA; matrixPieces[0][6] = horseA;
	matrixPieces[7][1] = horseH; matrixPieces[7][6] = horseH;
	//rookh
	matrixPieces[0][2] = rookhA; matrixPieces[0][5] = rookhA;
	matrixPieces[7][2] = rookhH; matrixPieces[7][5] = rookhH;
	//queen 
	if (colour[0] == 'b') {
		matrixPieces[0][4] = queenA;
		matrixPieces[0][3] = kingA;

		matrixPieces[7][4] = queenH;
		matrixPieces[7][3] = kingH;
	}
	else {
		matrixPieces[0][3] = queenA;
		matrixPieces[0][4] = kingA;

		matrixPieces[7][3] = queenH;
		matrixPieces[7][4] = kingH;
	}
	//king
	//matrixPieces[0][0] = elephantA; 
}

//draw the front page of the program
void frontPageDraw(HWND hWnd) {
	//Start code
	int numB = 2;
	float buttonRatio = 1.0 / (2.0 * numB);
	
	// Create button START
	hwndButton = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"ENTER SUMMONER",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		(int) (WINDOW_W*(1-buttonRatio) / 4.0),        // x position 
		WINDOW_L*(1 - buttonRatio) / 2,         // y position 
		(int)WINDOW_W * buttonRatio,        // Button width
		(int)WINDOW_L * buttonRatio,        // Button height
		hWnd,     // Parent window
		(HMENU)BUTTON_START_ID_MP,       // No menu.
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

}

/*
*BREIF : Draws teh checker board and the letters
*/
void gamePageDraw(HWND hWnd, HDC hdc ) {

	//Create exit buttons
	int spx_i = WINDOW_W / 50.0;
	int spy_i = WINDOW_L / 50.0;
	int spx = spx_i;   //starting x point 
	int spy = spy_i / 50.0;	// staring y point
	RECT recColour;    //object used for colouring rectangles

	
	hwndButton2 = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"EXIT BITCH",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		(int)2 * spx + widthSquare * 8,        // x position 
		(int)spy,       // y position 
		(int)widthSquare,        // Button width
		(int)widthSquare,        // Button height
		hWnd,     // Parent window
		(HMENU)BUTTON_EXIT_ID_MP,       // No menu.
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	//Draw board once
	int colour[2] = { COLOR_MENUTEXT , COLOR_INFOTEXT };   //dark , light
	for (int i = 0; i < 8; i++) {
		for (int y = 0; y < 8; y++) {
			Rectangle(hdc, spx, spy, (int)(spx + widthSquare), (int)(spy + widthSquare));
			recColour.left = spx;
			recColour.top = spy;
			recColour.right = (int)(spx + widthSquare);
			recColour.bottom = (int)(spy + widthSquare);
			FillRect(hdc, &recColour, (HBRUSH)colour[(i + y) % 2]);
			FrameRect(hdc, &recColour, (HBRUSH)COLOR_BACKGROUND);

			matrixSquareTile[i][y].coord[0] = (int)spx;
			matrixSquareTile[i][y].coord[1] = (int)spy;
			matrixSquareTile[i][y].background = (HBRUSH)colour[(i + y) % 2];

			spx = spx + widthSquare;
		}
		spy = spy + widthSquare;
		spx = spx_i;
	}

	//print all the pieces
	printPieces(hdc, matrixSquareTile, matrixPieces);
}

//draw all pieces
//6 minions
// 1 - King 2- QUEeen 3 - BISHOP 4-DONKEY 5-ELEPHANT - REST ARE ZERO
void printPieces(HDC hdc, SQUARETILE matrixSquareTile[8][8], chessPiece matrixRec[8][8]) {
	LPSTR str[6] = { "1","2","3","4","5","6" };
	LPSTR str1;
	for (int i = 0; i < 8; i++) {
		for (int y = 0; y < 8; y++) {
			switch (matrixRec[i][y].num) {
			case 1:
				TextOutA(hdc, matrixSquareTile[i][y].coord[0] + widthSquare / 2.0, matrixSquareTile[i][y].coord[1] + widthSquare / 2.0, str[0], strlen(str[0])); 
				if (matrixRec[i][y].colour == 'b')
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(0, 0, 0)), NULL);
				else
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(200, 200, 200)), NULL);
				break;
			case 2:
				TextOutA(hdc, matrixSquareTile[i][y].coord[0] + widthSquare / 2.0, matrixSquareTile[i][y].coord[1] + widthSquare / 2.0, str[1], strlen(str[1]));
				if (matrixRec[i][y].colour == 'b')
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(0, 0, 0)), NULL);
				else
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(200, 200, 200)), NULL);
				break;
			case 3:
				TextOutA(hdc, matrixSquareTile[i][y].coord[0] + widthSquare / 2.0, matrixSquareTile[i][y].coord[1] + widthSquare / 2.0, str[2], strlen(str[2]));
				if (matrixRec[i][y].colour == 'b')
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(0, 0, 0)), NULL);
				else
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(200, 200, 200)), NULL);
				break;
			case 4:
				TextOutA(hdc, matrixSquareTile[i][y].coord[0] + widthSquare / 2.0, matrixSquareTile[i][y].coord[1] + widthSquare / 2.0, str[3], strlen(str[3]));
				if (matrixRec[i][y].colour == 'b')
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(0, 0, 0)), NULL);
				else
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(200, 200, 200)), NULL);
				break;
			case 5:
				TextOutA(hdc, matrixSquareTile[i][y].coord[0] + widthSquare / 2.0, matrixSquareTile[i][y].coord[1] + widthSquare / 2.0, str[4], strlen(str[4]));
				if (matrixRec[i][y].colour == 'b')
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(0, 0, 0)), NULL);
				else
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(200, 200, 200)), NULL);
				break;
			case 6:
				TextOutA(hdc, matrixSquareTile[i][y].coord[0] + widthSquare / 2.0, matrixSquareTile[i][y].coord[1] + widthSquare / 2.0, str[5], strlen(str[5]));
				if (matrixRec[i][y].colour == 'b')
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(0, 0, 0)), NULL);
				else
					drawRectangle(hdc, matrixSquareTile[i][y].coord[0], matrixSquareTile[i][y].coord[1], matrixSquareTile[i][y].coord[0] + 20, matrixSquareTile[i][y].coord[1] + 20, CreateSolidBrush(RGB(200, 200, 200)), NULL);
				break;
			}
		}
	}
}

/*
*BREIF :Draws A rectanlge based on the COORDINATES , BACKGROUND and FRAME
*/
void drawRectangle(HDC hdc,int left,int top,int right,int bottom,HBRUSH back, HBRUSH frame  ) {
	RECT recColour;

	Rectangle(hdc, left, top, right, bottom);
	recColour.left = left;
	recColour.top = top;
	recColour.right = right;
	recColour.bottom = bottom;
	if (back != NULL) {
		FillRect(hdc, &recColour, back);
	}

	if (frame != NULL) {
		FrameRect(hdc, &recColour, frame);
	}
}


//responds when a tile is clicked to decide weather to highlight ,unhighlight or move a piece
void squareClickResponse(HDC hdc) {
	//if same square unhighlight it 
	int XIndex = squareClickedCoords.virtualX;
	int YIndex = squareClickedCoords.virtualY;
	int pXIndex = prevClicked.virtualX;
	int pYIndex = prevClicked.virtualY;

	if (matrixSquareTile[YIndex][XIndex].clicked == true) {

		twiceSameClickedSequence(hdc, XIndex, YIndex);
	}

	else if (clickedOnce == true) {
		twiceDifferentClickedSequence(hdc, XIndex, YIndex, pXIndex, pYIndex);
	}
	else if (clickedOnce == false)
	{
		//check if square even needs ot be highlighted
		//RULE 1 : NO MORE THAN ONE SQUARE CAN BE CLICKED			CHECK
		//RULE 2 : SQUARE THAT IS CLICKED MUST HAV ESOMETHING IN IT  CHECK
		//RULE 3 : SQUARE CLICKED THIRD TIME MUST NOT HAVE ANYTHING IN IT
		onceClickedSequence(hdc, XIndex, YIndex);
	}
}

//when click on a tile tile with a piece twice
//unlights if it detect it was clicked once already
void twiceSameClickedSequence(HDC hdc, int XIndex, int YIndex) {
	drawRectangle(hdc,
		squareClickedCoords.actualX,
		squareClickedCoords.actualY,
		squareClickedCoords.actualX + widthSquare,
		squareClickedCoords.actualY + widthSquare,
		matrixSquareTile[YIndex][XIndex].background,
		NULL);

	matrixSquareTile[YIndex][XIndex].clicked = false;
	printPieces(hdc, matrixSquareTile, matrixPieces);
	clickedOnce = false;    //ensures can only click one square at a time

}

//higlight square if data present
void onceClickedSequence(HDC hdc, int XIndex, int YIndex) {
	if ((matrixPieces[YIndex][XIndex].num) != 0) {
		if (matrixPieces[YIndex][XIndex].colour == turnColour){
			//higlight the rectangle
			drawRectangle(hdc,
				squareClickedCoords.actualX,
				squareClickedCoords.actualY,
				squareClickedCoords.actualX + widthSquare,
				squareClickedCoords.actualY + widthSquare,
				tileHighlightColour,
				NULL);

			// print out game display to redisplay characters
			printPieces(hdc, matrixSquareTile, matrixPieces);

			prevClicked.actualX = squareClickedCoords.actualX;
			prevClicked.actualY = squareClickedCoords.actualY;
			prevClicked.virtualX = squareClickedCoords.virtualX;
			prevClicked.virtualY = squareClickedCoords.virtualY;

			matrixSquareTile[YIndex][XIndex].clicked = true;
			clickedOnce = true;
		}
	}
}

//mocves piece to empty or enemy tile if this is the second click not on the same tile
void twiceDifferentClickedSequence(HDC hdc, int XIndex, int YIndex, int pXIndex, int pYIndex) {
	//see if the square clicked on is empty or is enemy

	if ((matrixPieces[YIndex][XIndex].num) == 0 || matrixPieces[YIndex][XIndex].colour != matrixPieces[pYIndex][pXIndex].colour) {
		//rules applied
		if (checkMovementRules(
			squareClickedCoords,
			prevClicked,
			matrixPieces[pYIndex][pXIndex].num,
			matrixPieces)
			) {

			//if empty change matrixRect
			matrixPieces[YIndex][XIndex] = matrixPieces[pYIndex][pXIndex];
			matrixPieces[pYIndex][pXIndex].num = 0;
			matrixPieces[pYIndex][pXIndex].colour = 'n';
			matrixPieces[pYIndex][pXIndex].atHome = false;

			//change turns
			if (turnColour == 'w') {
				turnColour = 'b';

			}
			else if (turnColour == 'b') {
				turnColour = 'w';
			}

			// print out game display to redisplay characters
			printPieces(hdc, matrixSquareTile, matrixPieces);

			//print out background on empty square and reset clicked matrix
			drawRectangle(hdc,
				prevClicked.actualX,
				prevClicked.actualY,
				prevClicked.actualX + widthSquare,
				prevClicked.actualY + widthSquare,
				matrixSquareTile[pYIndex][pXIndex].background,
				NULL);

			matrixSquareTile[pYIndex][pXIndex].clicked = false;
			clickedOnce = false;
		}
	}
}


//THING TO ADDF
//
//special moiinon kill rule which makes it go diagonal
//end of the line rule where you can change the chracters into something stronger
/**
* BREIF : Check if the movement received thoruhg inputs is accroding to chess rules
* RETURN : TRUE is all rules met else FALSE
*/
bool checkMovementRules(coordHolder current, coordHolder previous, int pieceNum, chessPiece matrixRec[8][8]) {
	//keep in mind that the piece has not moved yet
	float mag;
	float diffX = current.virtualX - previous.virtualX;
	float diffY = current.virtualY - previous.virtualY;
	int tempX = previous.virtualX, tempY = previous.virtualY;
	int directionY = diffY / abs((int)diffY);
	int directionX = diffX / abs((int)diffX);
	switch (pieceNum) {
		//KING 
	case 1:
		//calculate magnitude
		mag = sqrt(diffX*diffX + diffY*diffY);
		if (mag > 1.5) {
			return false;
		}
		break;
		//QUEEN
	case 2:
		//case one
		if (diffY == 0 || diffX == 0 || diffX == diffY || diffX == -diffY) {
			//find out if something in the way
			return (pathCheck(diffX, diffY, directionX, directionY, tempX, tempY, matrixRec));
		}
		else {
			return false;
		}
		break;
		//ROOKH
	case 3:
		if (diffX == diffY || diffX == -diffY) {
			//fiond out if something in the way
			return (pathCheck(diffX, diffY, directionX, directionY, tempX, tempY, matrixRec));
		}
		else {
			return false;
		}
		break;
		//horse
	case 4:
		if ((abs((int)diffY) == 2 && abs((int)diffX) == 1) ||
			(abs((int)diffX) == 2 && abs((int)diffY) == 1)) {
		}
		else {
			return false;
		}
		break;
		//elephant
	case 5:
		if (diffX == 0.0 || diffY == 0) {
			//find out if something in way
			return (pathCheck(diffX, diffY, directionX, directionY, tempX, tempY, matrixRec));
		}
		//
		else {
			return false;
		}
		break;

		//Minion
	case 6:
		//NOTE : three things
		//1 : are restrticted to move either one or down
		//2 :can move tweo steps sometimes and move sideways in soecial case
		//3 :can turn into power shits when reach otehr side
		if (matrixRec[tempY][tempX].colour == homeColour) {
			if (diffY == -1 && diffX == 0) {}
			else if (diffY == -2 && diffX == 0 && matrixRec[tempY][tempX].atHome == true) {}
			else if (diffY == -1 && abs((int)diffX) == 1) {  //cut another piece
				if (matrixRec[current.virtualY][current.virtualX].colour != matrixRec[previous.virtualY][previous.virtualX].colour) {}
				else { return false; }
			}
			else { return false; }
		}
		else {
			if (diffY == 1 && diffX == 0) {}   //move strright
			else if (diffY == 2 && diffX == 0 && matrixRec[tempY][tempX].atHome == true) {}  //move tow spaces
			else if (diffY == 1 && abs((int)diffX) == 1) {  //cut another piece
				if (matrixRec[current.virtualY][current.virtualX].colour != matrixRec[previous.virtualY][previous.virtualX].colour) {}
				else { return false; }
			}			
			else { return false; };
		}
		matrixRec[tempY][tempX].atHome = false;
		break;
	}
	return true;
}

/*
*BRIEF :check the path based on the coordinates recieved
*For ELEPHANT, ROOKH, QUEEN
*/
bool pathCheck(float diffX, float diffY, int directionX, int directionY, int tempX, int tempY, chessPiece matrixRec[8][8]) {
	for (int i = 0; i < abs((int)diffY) - 1; i++) {
		if (matrixRec[tempY + directionY][tempX + directionX].num != 0) {
			return false;
		}
		tempY = tempY + directionY;
		tempX = tempX + directionX;
	}
	return true;
}

//assign arrya 0,1 the coordinates of the rectanged
//assigns a,b the tile number
//return true if clicked on actual tile
bool getTilePressed(int x, int y) {
	squareClickedCoords.actualX = -1;
	squareClickedCoords.actualY = -1;
	squareClickedCoords.virtualX = -1;
	squareClickedCoords.virtualY = -1;
	//x,y and tile no(x,y)
	int a, b;

	//break if not in reigon
	if (x > matrixSquareTile[7][7].coord[0] + widthSquare || y >matrixSquareTile[7][7].coord[1] + widthSquare) {
		return false;
	}

	//find coords and index of click
	for (a = 0; a < 8; a++) {
		for (b = 0; b < 8; b++) {
			if (x < (matrixSquareTile[a][b].coord[0] + widthSquare)) {
				break;
			}
		}
		if (y < (matrixSquareTile[a][b].coord[1] + widthSquare)) {
			squareClickedCoords.actualX = matrixSquareTile[a][b].coord[0];
			squareClickedCoords.actualY = matrixSquareTile[a][b].coord[1];
			break;
		}
	}
	squareClickedCoords.virtualX = b;
	squareClickedCoords.virtualY = a;

	if (squareClickedCoords.virtualX == -1) {
		return false;
	}
	else {
		return true;
	}
}