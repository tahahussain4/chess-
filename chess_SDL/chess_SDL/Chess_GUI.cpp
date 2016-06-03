//INLCUDES and DEFINES
#include "stdafx.h"
#include "chess_GUI.h"
#include "math.h"
//===================================================FUCNTION POTOTYPES===============================
//FUNCTION prototyprd
bool checkMovementRules(coordHolder current, coordHolder previous, int pieceNumint);
bool rulesKingCheck(float diffX, float diffY, int comingFromX, int comingFromY);
bool rulesQueenCheck(float diffX, float diffY, int directionX, int directionY, int comingFromX, int comingFromY);
bool rulesRookhCheck(float diffX, float diffY, int directionX, int directionY, int comingFromX, int comingFromY);
bool rulesHorseCheck(float diffX, float diffY);
bool rulesElephantCheck(float diffX, float diffY, int directionX, int directionY, int comingFromX, int comingFromY);
bool rulesMinionCheck(float diffX, float diffY, int directionX, int directionY, int comingFromX, int comingFromY, int goingToY, int goingToX);
bool pathCheck(float diffX, float diffY, int directionX, int directionY, int tempX, int tempY, chessPiece matrixRec[8][8]);

//detect for check situation
bool checkDetect(coordHolder goingTo, coordHolder comingFrom);
void friendlyKingPos(chessPiece tempStorage[8][8], int kingPos[2]);
bool checkKing(int i, int j, int kingPos[2]);
bool checkQueen(chessPiece tempStorage[8][8], int i, int j);
bool checkRookh(chessPiece tempStorage[8][8], int i, int j);
bool checkHorse(int i, int j, int kingPos[2]);
bool checkElephant(chessPiece tempStorage[8][8], int i, int j);
bool checkMinion(int i, int j, int kingPos[2], char colour);
bool pathExplorer(chessPiece tempStorage[8][8], int arrayDir[8][2], int xPos, int yPos);

//click relkated functions
void twiceSameClickedSequence(HDC hdc, int XIndex, int YIndex);
void onceClickedSequence(HDC hdc, int XIndex, int YIndex);
void twiceDifferentClickedSequence(HDC hdc, int XIndex, int YIndex, int pXIndex, int pYIndex);

//printing on display funcitons
void printTextDrawRect(HDC hdc, int xPos, int yPos, LPSTR str[6], int piece);
void printPieces(HDC hdc, SQUARETILE matrixSquareTile[8][8]);

//higlight moves
int possibleMovesHiglight(HDC hdc, bool highlight, coordHolder squareClickedCoords);
void pathExplorerPossibleMoves(HDC hdc, chessPiece matrixPieces[8][8], int arrayDir[8][2], int xPos, int yPos, bool highlight);


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
bool				castlingFlag = false;

//===========================DRAW FUCNTIONS=============================

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
	minionA.num = MINION; minionA.colour = colour[0];

	//elephant
	elephantA.num = ELEPHANT; elephantA.colour = colour[0];

	//horse
	horseA.num = HORSE; horseA.colour = colour[0];

	//rookh
	rookhA.num = ROOKH; rookhA.colour = colour[0];

	//queen
	queenA.num = QUEEN; queenA.colour = colour[0];

	//king
	kingA.num = KING; kingA.colour = colour[0];

	//HOME---------

	//minions
	minionH.num = MINION; minionH.colour = colour[1];

	//elephHnt
	elephantH.num = ELEPHANT; elephantH.colour = colour[1];

	//horse
	horseH.num = HORSE; horseH.colour = colour[1];

	//rookh
	rookhH.num = ROOKH; rookhH.colour = colour[1];

	//queen
	queenH.num = QUEEN; queenH.colour = colour[1];

	//king
	kingH.num = KING; kingH.colour = colour[1];

	//fill array HOME and AWAY -------------
	//minion
	for (int xPos = 0; xPos < 8; xPos++) {
		matrixPieces[1][xPos] = minionA;
		matrixPieces[6][xPos] = minionH;
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
	
	//queen and king
	//they are arranged differently based on which side black and whites are
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

//BREIF : Draws teh checker board and the letters
void gamePageDraw(HWND hWnd, HDC hdc ) {

	//Create exit buttons
	int spx_initial = WINDOW_W / 50.0;
	int spy_initital = WINDOW_L / 50.0;
	int spx = spx_initial;   //starting x point 
	int spy = spy_initital / 50.0;	// staring y point
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
	int colour[2] = { TILECOLOURONE , TILECOLOURTWO };   //dark , light
	for (int yPos = 0; yPos < 8; yPos++) {
		for (int xPos = 0; xPos < 8; xPos++) {
			Rectangle(hdc, spx, spy, (int)(spx + widthSquare), (int)(spy + widthSquare));
			recColour.left = spx;
			recColour.top = spy;
			recColour.right = (int)(spx + widthSquare);
			recColour.bottom = (int)(spy + widthSquare);
			FillRect(hdc, &recColour, (HBRUSH)colour[(yPos + xPos) % 2]);
			FrameRect(hdc, &recColour, (HBRUSH)COLOR_BACKGROUND);

			matrixSquareTile[yPos][xPos].coord[0] = (int)spx;
			matrixSquareTile[yPos][xPos].coord[1] = (int)spy;
			matrixSquareTile[yPos][xPos].background = (HBRUSH)colour[(yPos + xPos) % 2];

			spx = spx + widthSquare;
		}
		spy = spy + widthSquare;
		spx = spx_initial;
	}

	//print all the pieces
	printPieces(hdc, matrixSquareTile);
}

//draw all pieces
//6-minions  1 - King 2- QUEeen 3 - BISHOP 4-DONKEY 5-ELEPHANT - REST ARE ZERO
void printPieces(HDC hdc, SQUARETILE matrixSquareTile[8][8]) {
	LPSTR str[6] = { "1","2","3","4","5","6" };
	LPSTR str1;
	for (int yPos = 0; yPos < 8; yPos++) {
		for (int xPos = 0; xPos < 8; xPos++) {
			switch (matrixPieces[yPos][xPos].num) {
			case KING:
				printTextDrawRect(hdc, xPos, yPos, str, KING);
				break;
			case QUEEN:
				printTextDrawRect(hdc, xPos, yPos, str, QUEEN);
				break;
			case ROOKH:
				printTextDrawRect(hdc, xPos, yPos, str, ROOKH);
				break;
			case HORSE:
				printTextDrawRect(hdc, xPos, yPos, str, HORSE);
				break;
			case ELEPHANT:
				printTextDrawRect(hdc, xPos, yPos, str, ELEPHANT);
				break;
			case MINION:
				printTextDrawRect(hdc, xPos, yPos, str, MINION);
				break;
			}
		}
	}
}

//print texts in the centre of tile and draws wither a black or white colour
void printTextDrawRect(HDC hdc, int xPos,int yPos ,LPSTR str[6], int piece) {
	
	TextOutA(hdc, matrixSquareTile[yPos][xPos].coord[0] + widthSquare / 2.0, matrixSquareTile[yPos][xPos].coord[1] + widthSquare / 2.0, str[piece-1], strlen(str[piece-1]));
	if (matrixPieces[yPos][xPos].colour == 'b')
		drawSmallRectangle(hdc, matrixSquareTile[yPos][xPos].coord[0],
								matrixSquareTile[yPos][xPos].coord[1], 
								matrixSquareTile[yPos][xPos].coord[0] + (int)widthSquare /4.0,
								matrixSquareTile[yPos][xPos].coord[1] + (int)widthSquare / 4.0,
								darkColour,  NULL);
	else
		drawSmallRectangle(hdc, matrixSquareTile[yPos][xPos].coord[0],
			matrixSquareTile[yPos][xPos].coord[1],
			matrixSquareTile[yPos][xPos].coord[0] + (int)widthSquare / 4.0,
			matrixSquareTile[yPos][xPos].coord[1] + (int)widthSquare / 4.0,
			lightColour, NULL);
}

//BREIF :Draws A rectanlge based on the COORDINATES , BACKGROUND and FRAME. 
//Can only draw the checkboard dsquare rectangles
void drawRectangle(HDC hdc,int posX,int posY, HBRUSH back, HBRUSH frame  ) {
	RECT recColour;

	Rectangle(hdc, matrixSquareTile[posY][posX].coord[0],
		matrixSquareTile[posY][posX].coord[1], 
		matrixSquareTile[posY][posX].coord[0] + widthSquare, 
		matrixSquareTile[posY][posX].coord[1] + widthSquare);

	recColour.left = matrixSquareTile[posY][posX].coord[0];
	recColour.top = matrixSquareTile[posY][posX].coord[1];
	recColour.right = matrixSquareTile[posY][posX].coord[0] + widthSquare;
	recColour.bottom = matrixSquareTile[posY][posX].coord[1] + widthSquare;
	if (back != NULL) {
		FillRect(hdc, &recColour, back);
	}

	if (frame != NULL) {
		FrameRect(hdc, &recColour, frame);
	}
}

void drawSmallRectangle(HDC hdc, int left, int top,int right, int bottom, HBRUSH back, HBRUSH frame) {
	RECT recColour;

	Rectangle(hdc, left,
		top,
		right,
		bottom);

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

//=============================CLCIK FUNCTIONS==============================

//responds when a tile is clicked to decide weather to highlight ,unhighlight or move a piece
void squareClickResponse(HDC hdc) {
	//if same square unhighlight it 
	int XIndex = squareClickedCoords.virtualX;
	int YIndex = squareClickedCoords.virtualY;
	int pXIndex = prevClicked.virtualX;
	int pYIndex = prevClicked.virtualY;

	//same square clicked teice
	if (matrixSquareTile[YIndex][XIndex].clicked == true) {

		twiceSameClickedSequence(hdc, XIndex, YIndex);
	}
	//two different squares cliked
	else if (clickedOnce == true) {
		twiceDifferentClickedSequence(hdc, XIndex, YIndex, pXIndex, pYIndex);
	}
	//square clicked first time
	else if (clickedOnce == false)
	{
		//check if square even needs ot be highlighted
		//RULE 1 : NO MORE THAN ONE SQUARE CAN BE CLICKED			CHECK
		//RULE 2 : SQUARE THAT IS CLICKED MUST HAV ESOMETHING IN IT  CHECK
		//RULE 3 : SQUARE CLICKED THIRD TIME MUST NOT HAVE ANYTHING IN IT
		onceClickedSequence(hdc, XIndex, YIndex);
	}
}

//higlight square if data present
void onceClickedSequence(HDC hdc, int XIndex, int YIndex) {
	if ((matrixPieces[YIndex][XIndex].num) != EMPTY) {
		if (matrixPieces[YIndex][XIndex].colour == turnColour){
			//higlight the rectangle
			drawRectangle(hdc,
				XIndex,
				YIndex,
				tileHighlightColour,
				NULL);
			//higlight all possible moves
			possibleMovesHiglight(hdc,true,squareClickedCoords);

			// print out game display to redisplay characters
			printPieces(hdc, matrixSquareTile);

			prevClicked.actualX = squareClickedCoords.actualX;
			prevClicked.actualY = squareClickedCoords.actualY;
			prevClicked.virtualX = squareClickedCoords.virtualX;
			prevClicked.virtualY = squareClickedCoords.virtualY;

			matrixSquareTile[YIndex][XIndex].clicked = true;
			clickedOnce = true;
		}
	}
}

//unlights if it detect it was clicked once already
void twiceSameClickedSequence(HDC hdc, int XIndex, int YIndex) {
	drawRectangle(hdc,
		XIndex,
		YIndex,
		matrixSquareTile[YIndex][XIndex].background,
		NULL);

	//unHiglighLight all moves;
	possibleMovesHiglight(hdc, false, squareClickedCoords);

	matrixSquareTile[YIndex][XIndex].clicked = false;
	printPieces(hdc, matrixSquareTile);
	clickedOnce = false;    //ensures can only click one square at a time

}

//mocves piece to empty or enemy tile if this is the second click not on the same tile
void twiceDifferentClickedSequence(HDC hdc, int XIndex, int YIndex, int pXIndex, int pYIndex) {
	//see if the square clicked on is empty or is enemy
	if ((matrixPieces[YIndex][XIndex].num) == 0 || matrixPieces[YIndex][XIndex].colour != matrixPieces[pYIndex][pXIndex].colour) {
		//rules applied
		if (checkDetect(squareClickedCoords, prevClicked) && checkMovementRules(
			squareClickedCoords,
			prevClicked,
			matrixPieces[pYIndex][pXIndex].num)
			 ){
			
			//Unllight possible moves from original position
			possibleMovesHiglight(hdc, false,prevClicked);

			//check for castling flag
			if (castlingFlag) {
				if (pXIndex > XIndex) {
					matrixPieces[YIndex][XIndex + 1] = matrixPieces[YIndex][0];
					matrixPieces[YIndex][XIndex + 1].atHome = false;

					matrixPieces[YIndex][0].num = EMPTY;
					matrixPieces[YIndex][0].colour = 'n';
					matrixPieces[YIndex][0].atHome = false;
					//draw on empty tile
					drawRectangle(hdc, 0, YIndex, matrixSquareTile[YIndex][0].background, NULL);

				}
				else {
					matrixPieces[YIndex][XIndex - 1] = matrixPieces[YIndex][7];
					matrixPieces[YIndex][XIndex - 1].atHome = false;

					matrixPieces[YIndex][7].num = EMPTY;
					matrixPieces[YIndex][7].colour = 'n';
					matrixPieces[YIndex][7].atHome = false;
					//draw on empty tile
					drawRectangle(hdc, 7, YIndex, matrixSquareTile[YIndex][7].background, NULL);
				}
				castlingFlag = false;
			}

			//make trasition of matrix
			matrixPieces[YIndex][XIndex] = matrixPieces[pYIndex][pXIndex];
			matrixPieces[YIndex][XIndex].atHome =false;

			matrixPieces[pYIndex][pXIndex].num = EMPTY;
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
			printPieces(hdc, matrixSquareTile);

			//print out background on empty s
			drawRectangle(hdc,pXIndex,pYIndex,matrixSquareTile[pYIndex][pXIndex].background,NULL);

			matrixSquareTile[pYIndex][pXIndex].clicked = false;
			clickedOnce = false;
		}
	}
}

//assign arrya 0,1 the coordinates of the rectanged
//assigns a,b the tile number
//return true if clicked on actual tile
bool getTilePressed(int x, int y)  {

	//initialized to -1
	squareClickedCoords.actualX = -1;
	squareClickedCoords.actualY = -1;
	squareClickedCoords.virtualX = -1;
	squareClickedCoords.virtualY = -1;

	//x,y and tile no(x,y)
	int yPos, xPos;

	//break if not in reigon 
	//8x8 board
	if (x > matrixSquareTile[7][7].coord[xPosition] + widthSquare || y >matrixSquareTile[7][7].coord[yPosition] + widthSquare) {
		return false;
	}

	//find coords and index of click
	for (yPos = 0; yPos < 8; yPos++) {
		for (xPos = 0; xPos < 8; xPos++) {
			if (x < (matrixSquareTile[yPos][xPos].coord[xPosition] + widthSquare)) {
				break;
			}
		}
		if (y < (matrixSquareTile[yPos][xPos].coord[yPosition] + widthSquare)) {
			squareClickedCoords.actualX = matrixSquareTile[yPos][xPos].coord[xPosition];
			squareClickedCoords.actualY = matrixSquareTile[yPos][xPos].coord[yPosition];
			break;
		}
	}
	squareClickedCoords.virtualX = xPos;
	squareClickedCoords.virtualY = yPos;

	if (squareClickedCoords.virtualX == -1) {
		return false;
	}
	else {
		return true;
	}
}

//==================================== MOVEMENT RULES FUNCITONs =========================

//BREIF : Check if the movement received thoruhg inputs is accroding to chess rules. 
//RETURN : TRUE is all rules met else FALSE
bool checkMovementRules(coordHolder current, coordHolder previous, int pieceNum) {
	//NOTE: keep in mind that the piece has not moved yet for the first part of the check
	//NOTE : deos reset atHome flags so should be the LAST CHECK before moving
	float diffX = current.virtualX - previous.virtualX;
	float diffY = current.virtualY - previous.virtualY;
	int comingFromX = previous.virtualX, comingFromY = previous.virtualY;
	int goingToX = current.virtualX, goingToY = current.virtualY;
	int directionY, directionX;

	//specifying x,y direction 
	if (diffY != 0) {
		directionY = diffY / abs((int)diffY);
	}
	else {
		directionY = 0;
	}

	if (diffX != 0) {
		directionX = diffX / abs((int)diffX);
	}
	else {
		directionX = 0;
	}

	switch (pieceNum) {
	//KING 
	case KING:
		if (rulesKingCheck(diffX,diffY,comingFromX,comingFromY)) {}
		else { return false; }
		break;
	//QUEEN
	case QUEEN:
		if (rulesQueenCheck(diffX,  diffY,  directionX,  directionY,  comingFromX,  comingFromY)) {}
		else { return false; }
		break;
	//ROOKH
	case ROOKH:
		if (rulesRookhCheck( diffX,  diffY,  directionX,  directionY,  comingFromX,  comingFromY)) {}
		else { return false; }
		break;
	//horse
	case HORSE:
		if (rulesHorseCheck( diffX,  diffY)) {}
		else { return false; }
		break;
	//elephant
	case ELEPHANT:
		if (rulesElephantCheck( diffX,  diffY,  directionX,  directionY,  comingFromX,  comingFromY)) {}
		else { return false; }
		break;
	//Minion
	case MINION:
		if (rulesMinionCheck( diffX,  diffY,  directionX,  directionY,  comingFromX,  comingFromY,  goingToY,  goingToX)) {}
		else { return false; }
		break;
	}

	return true;
}

//see if king movement obeys the movement rules
bool rulesKingCheck(float diffX, float diffY,int comingFromX,int comingFromY) {
	//calculate magnitude
	//pieces hacvent moved yet
	float mag;
	mag = sqrt(diffX*diffX + diffY*diffY);
	//check for castling
	if (matrixPieces[comingFromY][comingFromX].atHome == true) {
		if (diffX == 2 && matrixPieces[comingFromY][7].atHome == true) {
			if (homeColour == 'b' && matrixPieces[comingFromY][comingFromX + 1].num==EMPTY
				&& matrixPieces[comingFromY][comingFromX + 2].num == EMPTY){
				castlingFlag = true;
				return(true);
			}
			else if(homeColour == 'w' && matrixPieces[comingFromY][comingFromX + 1].num == EMPTY
				&& matrixPieces[comingFromY][comingFromX + 2].num == EMPTY
				&& matrixPieces[comingFromY][comingFromX + 3].num == EMPTY){
				castlingFlag = true;
				return(true);
			}
			else return false;
		}
		if (diffX == -2 && matrixPieces[comingFromY][0].atHome == true) {
			if (homeColour == 'w' && matrixPieces[comingFromY][comingFromX - 1].num == EMPTY
				&& matrixPieces[comingFromY][comingFromX - 2].num == EMPTY) {
				castlingFlag = true;
				return(true);
			}
			else if (homeColour == 'b' && matrixPieces[comingFromY][comingFromX - 1].num == EMPTY
				&& matrixPieces[comingFromY][comingFromX - 2].num == EMPTY
				&& matrixPieces[comingFromY][comingFromX - 3].num == EMPTY) {
				castlingFlag = true;
				return(true);
			}
			else return false;
		}
	}

	if (mag > 1.5) {
		return false;
	}

	return true;
}

//see if queen movement obeys the movement rules
bool rulesQueenCheck(float diffX, float diffY,int directionX, int directionY, int comingFromX, int comingFromY) {
	//case one

	if (diffY == 0 || diffX == 0 || diffX == diffY || diffX == -diffY) {
		//find out if something in the way
		if (!pathCheck(diffX, diffY, directionX, directionY, comingFromX, comingFromY, matrixPieces)) { return false; };
	}
	else { return false; }

	return true;
}

//see if rookh movement obeys the movement rules
bool rulesRookhCheck(float diffX, float diffY, int directionX, int directionY, int comingFromX, int comingFromY) {
	if (diffX == diffY || diffX == -diffY) {
		//fiond out if something in the way
		if (!pathCheck(diffX, diffY, directionX, directionY, comingFromX, comingFromY, matrixPieces)) { return false; };
	}
	else {
		return false;
	}
	return true;
}

//see if horse movement obeys the movement rules
bool rulesHorseCheck(float diffX, float diffY) {
	if ((abs((int)diffY) == 2 && abs((int)diffX) == 1) ||
		(abs((int)diffX) == 2 && abs((int)diffY) == 1)) {
	}
	else {
		return false;
	}
	return true;
}

//see if elephant movement obeys the movement rules
bool rulesElephantCheck(float diffX, float diffY, int directionX, int directionY, int comingFromX, int comingFromY) {
	
	if (diffX == 0.0 || diffY == 0) {

		//find out if something in way
		if (!pathCheck(diffX, diffY, directionX, directionY, comingFromX, comingFromY, matrixPieces)) { return false; };
	} 		//
	else {
		return false;
	}
	return true;
}

//see if minon movement obeys chess rules
bool rulesMinionCheck(float diffX, float diffY, int directionX, int directionY, int comingFromX, int comingFromY ,int goingToY, int goingToX) {
	//NOTE : 
	//1 : are restrticted to move either one or down
	//2 :can move tweo steps sometimes and move sideways in soecial case
	//3 :can turn into power shits when reach otehr side
	//4 : can not cut by moving strasight but only sideways
	//5 when cutting siudeways make sure somethign is there

	if (matrixPieces[comingFromY][comingFromX].colour == homeColour) {
		if (diffY == -1 && diffX == 0 && matrixPieces[goingToY][goingToX].num == EMPTY) {
			matrixPieces[comingFromY][comingFromX].atHome = false;
		}
		else if (diffY == -2 && diffX == 0 && matrixPieces[comingFromY][comingFromX].atHome == true && matrixPieces[goingToY][goingToX].num == EMPTY) {
			matrixPieces[comingFromY][comingFromX].atHome = false;
		}
		else if (diffY == -1 && (abs((int)diffX) == 1) && matrixPieces[goingToY][goingToX].num != EMPTY) {  //cut another piece
			matrixPieces[comingFromY][comingFromX].atHome = false;
		}
		else { return false; }
	}
	else {
		if (diffY == 1 && diffX == 0 && matrixPieces[goingToY][goingToX].num == EMPTY) {
			matrixPieces[comingFromY][comingFromX].atHome = false;
		}   
		else if (diffY == 2 && diffX == 0 && matrixPieces[comingFromY][comingFromX].atHome == true && matrixPieces[goingToY][goingToX].num == EMPTY) {
			matrixPieces[comingFromY][comingFromX].atHome = false;
		}  
		else if (diffY == 1 && abs((int)diffX) == 1 && matrixPieces[goingToY][goingToX].num != EMPTY) {  //cut another piece
			matrixPieces[comingFromY][comingFromX].atHome = false;
		}
		else { return false; };
	}
	return true;
}

//BRIEF :check the path for obstructions based on the coordinates recieved
//For ELEPHANT, ROOKH, QUEEN
bool pathCheck(float diffX, float diffY, int directionX, int directionY, int tempX, int tempY, chessPiece matrixRec[8][8]) {
	
	for (int i = 0; i < max(abs((int)diffX), abs((int)diffY)) - 1; i++) {
		if (matrixRec[tempY + directionY][tempX + directionX].num != EMPTY) {
			return false;
		}
		tempY = tempY + directionY;
		tempX = tempX + directionX;
	}
	return true;
}

//===================================CHECK SITUATIONS FUNCTIONS =============================

//detects if move will lead to a check postion which has been present or made due to move
bool checkDetect(coordHolder goingTo, coordHolder comingFrom) {
	//====================================================================================
	//===================================================================================
	int goingToX = goingTo.virtualX;
	int goingToY = goingTo.virtualY;
	int comingFromX = comingFrom.virtualX;
	int comingFromY = comingFrom.virtualY;

	//TEST FOR KING IN HARMS WAY - KEEP IN MIND THAT PIECE WILL BE MOVED TO GET NEW PATHS

	//make a copy of the old matrix
	chessPiece tempStorage[8][8];
	for (int k = 0; k < 8; k++) {
		for (int l = 0; l < 8; l++) {
			tempStorage[k][l] = matrixPieces[k][l];
		}
	}


	//assign new indices
	tempStorage[goingToY][goingToX] = tempStorage[comingFromY][comingFromX];
	tempStorage[comingFromY][comingFromX].num = 0;
	tempStorage[comingFromY][comingFromX].colour = 'n';
	tempStorage[comingFromY][comingFromX].atHome = false;


	//find pos of friendly king
	int kingPos[2] = { 0,0 };
	friendlyKingPos(tempStorage, kingPos);

	//find enemies in new matrix and check path for overlay with king
	for (int yPos = 0; yPos < 8; yPos++) {
		for (int xPos = 0; xPos < 8; xPos++) {
			//not friendly colour and is not empty
			if (tempStorage[yPos][xPos].colour != turnColour && tempStorage[yPos][xPos].num != EMPTY) {

				switch (tempStorage[yPos][xPos].num) {
				//KING
				case KING:
					if(checkKing(yPos,xPos,kingPos)){}
					else { return false; }
					break;
				//QUEEN
				case QUEEN:
					if (checkQueen(tempStorage, yPos, xPos)) {}
					else { return false; }
					break;
				//ROOKH
				case ROOKH:
					if (checkRookh(tempStorage, yPos, xPos)) {}
					else { return false; }
					break;

				//HORSE
				case HORSE:
					if (checkHorse(yPos, xPos, kingPos)) {}
					else { return false; }
					break;
				//ELEPHANT
				case ELEPHANT:
					//go through the  paths
					if (checkElephant(tempStorage, yPos, xPos)) {}
					else { return false; }
					break;
				//MINION
				case MINION:
					if (checkMinion(yPos, xPos, kingPos, tempStorage[yPos][xPos].colour)) {}
					else { return false; }
					break;

				}
			}
		}
	}
	return true;
}

//see if check can be caused by king
bool checkKing(int yPos,int xPos ,int kingPos[2]) {
	if ((yPos + 1 == kingPos[0] && xPos + 0 == kingPos[1]) ||
		(yPos + 1 == kingPos[0] && xPos + 1 == kingPos[1]) ||
		(yPos + 1 == kingPos[0] && xPos - 1 == kingPos[1]) ||
		(yPos - 1 == kingPos[0] && xPos + 0 == kingPos[1]) ||
		(yPos - 1 == kingPos[0] && xPos + 1 == kingPos[1]) ||
		(yPos - 1 == kingPos[0] && xPos - 1 == kingPos[1]) ||
		(yPos + 0 == kingPos[0] && xPos + 1 == kingPos[1]) ||
		(yPos + 0 == kingPos[0] && xPos - 1 == kingPos[1])) {

		return false;
	}

	return true;
}

//see if check can be caused by queen
bool checkQueen(chessPiece tempStorage[8][8], int yPos, int xPos) {
	int queenDir[8][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 },{ 1,1 },{ -1,-1 },{ -1,1 },{ 1,-1 } };
	return(pathExplorer(tempStorage, queenDir, xPos,yPos));
}

//see if check casued by rookh
bool checkRookh(chessPiece tempStorage[8][8], int yPos, int xPos) {
	int rookhDir[4][2] = { { 1,1 },{ -1,-1 },{ -1,1 },{ 1,-1 } };
	return(pathExplorer(tempStorage, rookhDir, xPos, yPos));
}

//see if check caused by horse
bool checkHorse(int i, int j, int kingPos[2]) {
	if ((i + 2 == kingPos[0] && j + 1 == kingPos[1]) ||
		(i + 2 == kingPos[0] && j - 1 == kingPos[1]) ||
		(i - 2 == kingPos[0] && j + 1 == kingPos[1]) ||
		(i - 2 == kingPos[0] && j - 1 == kingPos[1]) ||
		(i + 1 == kingPos[0] && j + 2 == kingPos[1]) ||
		(i + 1 == kingPos[0] && j - 2 == kingPos[1]) ||
		(i - 1 == kingPos[0] && j + 2 == kingPos[1]) ||
		(i - 1 == kingPos[0] && j - 2 == kingPos[1])) {
		return false;
	}
	
	return true;
}

//see if check caused by elephant
bool checkElephant(chessPiece tempStorage[8][8], int yPos, int xPos) {
	int eleDir[4][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };
	return(pathExplorer(tempStorage, eleDir, xPos, yPos));
}

//see if check caused by Minion
bool checkMinion(int i, int j, int kingPos[2],char colour) {
	if  (colour ==homeColour &&
		((i - 1 == kingPos[0] && j + 1 == kingPos[1]) || (i - 1 == kingPos[0] && j -1 == kingPos[1])) ) {

		return false;
	}
	else if (colour != homeColour &&
		((i + 1 == kingPos[0] && j + 1 == kingPos[1]) || (i + 1 == kingPos[0] && j - 1 == kingPos[1]))) {
		return false;
	}
	return true;
}

//going over all path to check for CEHCK conditions
bool pathExplorer(chessPiece tempStorage[8][8] , int arrayDir[8][2], int xPos, int yPos) {

	int yDir = 0, xDir = 1;
	int arraySize = 0;
	if (tempStorage[yPos][xPos].num == QUEEN) {
		arraySize = 8;
	}
	else {
		arraySize = 4;
	}

	for (int path = 0; path < arraySize; path++) {
		for (int b = 1; b < 8; b++) {  //excluede itself so no 0

			 //if reach end of matrix then break
			if (yPos + b*arrayDir[path][yDir] == 8 || xPos + b*arrayDir[path][xDir] == 8
				|| yPos + b*arrayDir[path][yDir] == -1 || xPos + b*arrayDir[path][xDir] == -1) {
				break;
			}

			//if land on a non number break 
			//if KING(1) of opposite team then false
			if (tempStorage[yPos + b*arrayDir[path][yDir]][xPos + b*arrayDir[path][xDir]].num != EMPTY) {
				if (tempStorage[yPos + b*arrayDir[path][yDir]] [xPos + b*arrayDir[path][xDir]].num == KING &&
					tempStorage[yPos + b*arrayDir[path][yDir]] [xPos + b*arrayDir[path][xDir]].colour == turnColour) {

					return false;
				}
				else break;
			}
		}
	}
	return true;
}

//find friendlyKingPos
//assign array sent, with the pararmterts
void friendlyKingPos(chessPiece tempStorage[8][8],int kingPos[2]) {
	int i, j = 0;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (tempStorage[i][j].num == 1 && tempStorage[i][j].colour == turnColour) {

				break;
			}
		}
		if (tempStorage[i][j].num == 1 && tempStorage[i][j].colour == turnColour) {
			kingPos[0] = i;   //y pos
			kingPos[1] = j;	  //x pos
			break;
		}
	}
}
// =====================================HIGLIGHT POSSIBLE MOVES ===================================
//higlighting possible moves
int possibleMovesHiglight(HDC hdc, bool highlight,coordHolder squareClickedCoords) {
	int xPos = squareClickedCoords.virtualX;
	int yPos = squareClickedCoords.virtualY;
	HBRUSH background;
	int minionDir = 0;
	int kingArray[8][2] =
	{ {yPos + 1, xPos + 0},
	{yPos + 1, xPos + 1},
	{yPos + 1, xPos - 1},
	{yPos - 1, xPos + 0},
	{yPos - 1, xPos + 1},
	{yPos - 1, xPos - 1},
	{yPos + 0, xPos + 1},
	{yPos + 0, xPos - 1} };
			
	int horseArray[8][2] =
	{ { yPos + 2, xPos + 1 },
	{ yPos + 2, xPos - 1 },
	{ yPos - 2, xPos + 1 },
	{ yPos - 2, xPos - 1 },
	{ yPos - 1, xPos + 2 },
	{ yPos - 1, xPos - 2 },
	{ yPos + 1, xPos + 2 },
	{ yPos + 1, xPos - 2 } };

	coordHolder temp;
	int queenDir[8][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 },{ 1,1 },{ -1,-1 },{ -1,1 },{ 1,-1 } };
	int rookhDir[4][2] = { { 1,1 },{ -1,-1 },{ -1,1 },{ 1,-1 } };
	int eleDir[4][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };



		switch (matrixPieces[yPos][xPos].num) {
			//KING 
		case KING:
			for (int ArrayCount = 0; ArrayCount < 8; ArrayCount++) {
				//index on board and index doesnt cover any friendly miinons
				if ((kingArray[ArrayCount][0] > -1) && (kingArray[ArrayCount][1] > -1) &&
					(kingArray[ArrayCount][0] < 8) && (kingArray[ArrayCount][1] < 8))
				{
					//if empty
					if (matrixPieces[kingArray[ArrayCount][0]][kingArray[ArrayCount][1]].num == EMPTY)
					{
						if (highlight == true) { background = EMPTYSPACES; }
						else { background = matrixSquareTile[kingArray[ArrayCount][0]][kingArray[ArrayCount][1]].background; }

						drawRectangle(hdc,
							kingArray[ArrayCount][1],
							kingArray[ArrayCount][0],
							background,
							lightColour);
					}
					//if enemy
					else if (matrixPieces[kingArray[ArrayCount][0]][kingArray[ArrayCount][1]].colour != turnColour) {
						if (highlight == true) { background = ENEMYCOLOUR; }
						else { background = matrixSquareTile[kingArray[ArrayCount][0]][kingArray[ArrayCount][1]].background; }

						drawRectangle(hdc,
							kingArray[ArrayCount][1],
							kingArray[ArrayCount][0],
							background,
							lightColour);
					}
				}
			}  

			//castling higlight
			if (matrixPieces[yPos][xPos].atHome == true) {
				if (homeColour == 'b') {
					//one on the right
					if (matrixPieces[yPos][7].atHome == true  
						&& matrixPieces[yPos][xPos + 1].num == EMPTY
						&& matrixPieces[yPos][xPos + 2].num == EMPTY
						&& checkDetect( { xPos,yPos }, { xPos + 2,yPos }) ) {
						//higlght the square xPos+2
						if (highlight == true) { background = CASTLECOLOUR; }
						else { background = matrixSquareTile[yPos][xPos+2].background; }
						drawRectangle(hdc,
							xPos + 2,
							yPos,
							background,
							lightColour);

					}
					//one on the left
					if (matrixPieces[yPos][0].atHome == true 
						&& matrixPieces[yPos][xPos - 1].num == EMPTY
						&& matrixPieces[yPos][xPos - 2].num == EMPTY
						&& matrixPieces[yPos][xPos - 3].num == EMPTY
						&& checkDetect({ xPos,yPos }, { xPos - 2,yPos })) {
						//higlight square xPos-2
						if (highlight == true) { background = CASTLECOLOUR; }
						else { background = matrixSquareTile[yPos][xPos - 2].background; }
						drawRectangle(hdc,
							xPos - 2,
							yPos,
							background,
							lightColour);
					}
				}
				
				if (homeColour == 'w') {
					//one on the right
					if (matrixPieces[yPos][7].atHome == true
						&& matrixPieces[yPos][xPos + 1].num == EMPTY
						&& matrixPieces[yPos][xPos + 2].num == EMPTY
						&& matrixPieces[yPos][xPos + 3].num == EMPTY
						&& checkDetect({ xPos,yPos }, { xPos + 2,yPos })) {
						//higlght the square xPos+2
						if (highlight == true) { background = CASTLECOLOUR; }
						else { background = matrixSquareTile[yPos][xPos + 2].background; }
						drawRectangle(hdc,
							xPos + 2,
							yPos,
							background,
							lightColour);

					}
					//one on the left
					if (matrixPieces[yPos][0].atHome == true
						&& matrixPieces[yPos][xPos - 1].num == EMPTY
						&& matrixPieces[yPos][xPos - 2].num == EMPTY
						&& checkDetect({ xPos,yPos }, { xPos - 2,yPos })) {
						//higlight square xPos-2
						if (highlight == true) { background = CASTLECOLOUR; }
						else { background = matrixSquareTile[yPos][xPos - 2].background; }
						drawRectangle(hdc,
							xPos - 2,
							yPos,
							background,
							lightColour);
					}
				}

			}
			break;
			//QUEEN
		case QUEEN:
			pathExplorerPossibleMoves(hdc, matrixPieces, queenDir, xPos, yPos,highlight);
			break;
			//ROOKH
		case ROOKH:
			pathExplorerPossibleMoves(hdc, matrixPieces, rookhDir, xPos, yPos,highlight);
			break;

			//HORSE
		case HORSE:
			for (int ArrayCount = 0; ArrayCount<8; ArrayCount++) {
				//index on board and index doesnt cover any friendly miinons
				if ((horseArray[ArrayCount][0] > -1) && (horseArray[ArrayCount][1] > -1) &&
					(horseArray[ArrayCount][0] < 8) && (horseArray[ArrayCount][1] < 8))
				{

					//if empty
					if (matrixPieces[horseArray[ArrayCount][0]][horseArray[ArrayCount][1]].num == EMPTY)
					{
						if (highlight == true) { background = EMPTYSPACES; }
						else { background = matrixSquareTile[horseArray[ArrayCount][0]][horseArray[ArrayCount][1]].background; }

						drawRectangle(hdc,
							horseArray[ArrayCount][1],
							horseArray[ArrayCount][0],
							background,
							lightColour);
					}
					//if enemy
					else if (matrixPieces[horseArray[ArrayCount][0]][horseArray[ArrayCount][1]].colour != turnColour) {
						if (highlight == true) { background = ENEMYCOLOUR; }
						else { background = matrixSquareTile[horseArray[ArrayCount][0]][horseArray[ArrayCount][1]].background; }

						drawRectangle(hdc,
							horseArray[ArrayCount][1],
							horseArray[ArrayCount][0],
							background,
							lightColour);
					}
				}
			}
			break;
			//ELEPHANT
		case ELEPHANT:
			pathExplorerPossibleMoves(hdc, matrixPieces, eleDir, xPos, yPos,highlight);
			break;
			//MINION
		case MINION:
			//selct which direction to higlight in 
			if (turnColour == homeColour) {
				minionDir = -1;
			}
			else {
				minionDir = +1;
			}

			//draw in front if empty
			if (matrixPieces[yPos + (1 * minionDir)][xPos].num == EMPTY) {
				//decide background
				if (highlight) { background = EMPTYSPACES; }
				else { background = matrixSquareTile[yPos + (1 * minionDir)][xPos].background; }

				drawRectangle(hdc, xPos, yPos + (1 * minionDir), background, lightColour);

				//if at home illumnintae second one as well
				if (matrixPieces[yPos][xPos].atHome == true && matrixPieces[yPos + (2*minionDir)][xPos].num == EMPTY) {
					background = EMPTYSPACES; 
					drawRectangle(hdc, xPos, yPos + (2 * minionDir), background, lightColour);
				}
				//unhiglight second if flag set
				if (!highlight) {
					background = matrixSquareTile[yPos + (2 * minionDir)][xPos].background;
					drawRectangle(hdc, xPos, yPos + (2 * minionDir), background, lightColour);
				}
			}
			//enemy turn organe
			if (matrixPieces[yPos + (1 * minionDir)][xPos - 1].num != EMPTY &&
				matrixPieces[yPos + (1 * minionDir)][xPos - 1].colour != turnColour) {
				if (highlight) { background = ENEMYCOLOUR; }
				else { background = matrixSquareTile[yPos + (1 * minionDir)][xPos-1].background; }
				drawRectangle(hdc,
					xPos - 1,
					yPos + (1 * minionDir),
					background,
					lightColour);
			}
			//enemy turn orange
			if (matrixPieces[yPos + (1 * minionDir)][xPos + 1].num != EMPTY &&
				matrixPieces[yPos + (1 * minionDir)][xPos + 1].colour != turnColour) {
				if (highlight) { background = ENEMYCOLOUR; }
				else { background = matrixSquareTile[yPos + (1 * minionDir)][xPos+1].background; }
				drawRectangle(hdc,
					xPos + 1,
					yPos + (1 * minionDir),
					background,
					lightColour);
			}
			

			break;

		}
			
	return 1;
}

//going over all path to check for CEHCK conditions
void pathExplorerPossibleMoves(HDC hdc, chessPiece matrixPieces[8][8], int arrayDir[8][2], int xPos, int yPos, bool highlight) {
	HBRUSH background;
	int yDir = 0, xDir = 1;
	int arraySize = 0;
	if (matrixPieces[yPos][xPos].num == QUEEN) {
		arraySize = 8;
	}
	else {
		arraySize = 4;
	}

	for (int path = 0; path < arraySize; path++) {
		for (int b = 1; b < 8; b++) {  //excluede itself so no 0

									   //if reach end of matrix then break
			if (yPos + b*arrayDir[path][yDir] == 8 || xPos + b*arrayDir[path][xDir] == 8
				|| yPos + b*arrayDir[path][yDir] == -1 || xPos + b*arrayDir[path][xDir] == -1) {
				break;
			}

			//if Empty keep going and higlight RED
			//if opposite colour higlight ORANGE
			//
			if (matrixPieces[yPos + b*arrayDir[path][yDir]][xPos + b*arrayDir[path][xDir]].num == EMPTY) {
				if (highlight) { background = EMPTYSPACES; }
				else {
					background = matrixSquareTile[yPos + b*arrayDir[path][yDir]][xPos + b*arrayDir[path][xDir]].background;
				}

				drawRectangle(hdc,
					xPos + b*arrayDir[path][xDir],					
					yPos + b*arrayDir[path][yDir],				
					background,
					lightColour);
			}
			else if(matrixPieces[yPos + b*arrayDir[path][yDir]][xPos + b*arrayDir[path][xDir]].colour != turnColour) {
				if (highlight) { background = ENEMYCOLOUR; }
				else {
					background = matrixSquareTile[yPos + b*arrayDir[path][yDir]][xPos + b*arrayDir[path][xDir]].background;
				}
				drawRectangle(hdc,
					xPos + b*arrayDir[path][xDir],
					yPos + b*arrayDir[path][yDir],
					background,
					lightColour);
				break;
			}
			else break;
		}
	}	
}

