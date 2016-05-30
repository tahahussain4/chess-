// chess_SDL.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "chess_SDL.h"
#include "Chess_GUI.h"

// Global Variables:
HINSTANCE			hInst;                                // current instance
WCHAR				szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR				szWindowClass[MAX_LOADSTRING];            // the main window class name
WNDCLASSEXW			wcex;

bool				frontPage = false;
bool				gamePage = true;
bool				bStartClicked,bExitClicked = false;
bool				squareClickedResponse = false;		//flag to response
bool				squareHoverResponse = false;



// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void				InitGame(HINSTANCE,int);
void				piecesInit();

//MAIN function
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHESS_SDL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHESS_SDL));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



///
///  FUNCTION: MyRegisterClass()
///
///  PURPOSE: Registers the window class.
///
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHESS_SDL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHESS_SDL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   //Create cloient window
   CREATESTRUCT cs;
   ZeroMemory(&cs, sizeof(cs));
   cs.x = 50;    // Window X position
   cs.y = 0;    // Window Y position
   cs.cx = WINDOW_W;  // Window width
   cs.cy = WINDOW_L;  // Window height
   cs.hInstance = hInstance; // Window instance.
   cs.lpszClass = wcex.lpszClassName;       // Window class name
   cs.lpszName = TEXT("My First Window");  // Window title
   cs.style = WS_OVERLAPPEDWINDOW;      // Window style

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   cs.x, cs.y, cs.cx, cs.cy, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //intialise pieces postions
   piecesInit();

   //update and show window
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);



   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int x; //getting x ocordinate
	int y; //getting y coordinate
	RECT lpRect; //getting 
	bool tilePressed;
	coordHolder hoverCoords;

    switch (message)
    {
    case WM_COMMAND:
        {	
			//button control
			int wmId = HIWORD(wParam);
			switch (wmId)
			{
			case BN_CLICKED:
				//Go thorugh different buttons
				wmId = LOWORD(wParam);
				switch (wmId)
				{
				case BUTTON_START_ID_MP:
					gamePage = true;
					EnableWindow(GetDlgItem(hWnd, BUTTON_START_ID_MP), false); //ID of button, NOT the handle 
					EnableWindow(GetDlgItem(hWnd, BUTTON_EXIT_ID_MP), false); //ID of button, NOT the handle 

					break;
				case BUTTON_EXIT_ID_MP:
					DestroyWindow(hWnd);
					break;
				}
				break;
			}

            wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
	{
		// TODO: Add any drawing code that uses hdc here...
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT recColour;
		int XIndex, YIndex ,pXIndex,pYIndex ;
		bool start;
		

		//draw front page
		//if (frontPage == true) {
			//frontPageDraw(hWnd);
			//frontPage == false;
		//}
		
		//draw Graphics page
		if (gamePage == true) {
			gamePageDraw(hWnd, hdc);
			gamePage = false;
		}

		//SQUARE CLCIK ----------------------------------------------------
		if (squareClickedResponse == true){
			squareClickResponse(hdc);
			squareClickedResponse = false;
		}		

		//SQUARE HOVER---------------------------------------------
		if (squareHoverResponse == true) {
			squareHoverResp(hdc);
			squareHoverResponse = false;
		}


		//AI processes its things and calls invalidate rect

    	// print Names
		LPCSTR str1 = "TAHA HUSSAIN";
		TextOutA(hdc, WINDOW_W - 150, WINDOW_L - 125, str1, strlen(str1));

		LPCSTR str2 = "PAUL LE";
		TextOutA(hdc, WINDOW_W - 150, WINDOW_L - 100, str2, strlen(str2));

        EndPaint(hWnd, &ps);
        }

		
		//CODE END:
        break;

	case WM_LBUTTONDOWN:
		//get mouse props
		x = LOWORD(lParam);
		y = HIWORD(lParam); 

		tilePressed = getTilePressed(x, y);

		//check if clicked on a valid squre
		//if not cliked break this function 
		//tilew index return
		if (!tilePressed) {
			break;
		}
		
		//set flag so WM_PAINT works
		squareClickedResponse = true;

		////call to draw a rectangle at that pos

		lpRect.left = 0;
		lpRect.top = 0;
		lpRect.right = WINDOW_W;
		lpRect.bottom = WINDOW_L;
		InvalidateRect(hWnd, &lpRect, false);
		break;

	//case WM_MOUSEMOVE:

	//	//get mouse props
	//	x = LOWORD(lParam);
	//	y = HIWORD(lParam);

	//	hoverCoords = getTileHover(x, y);
	//	if (hoverCoords.actualX == -1) {
	//		break;
	//	}
	//	squareHoverResponse = true;

	//	lpRect.left = 0;
	//	lpRect.top = 0;
	//	lpRect.right = WINDOW_W;
	//	lpRect.bottom = WINDOW_L;
	//	InvalidateRect(hWnd, &lpRect, false);

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//Make game window
void InitGame(HINSTANCE hInstance, int nCmdShow) {

	hInst = hInstance; // Store instance handle in our global variable
    //Struct
	CREATESTRUCT cs;
	ZeroMemory(&cs, sizeof(cs));
	cs.x = 500;    // Window X position
	cs.y = 0;    // Window Y position
	cs.cx = WINDOW_W;  // Window width
	cs.cy = WINDOW_L;  // Window height
	cs.hInstance = hInstance; // Window instance.
	cs.lpszClass = wcex.lpszClassName;       // Window class name
	cs.lpszName = TEXT("My Game Window");  // Window title
	cs.style = WS_OVERLAPPEDWINDOW;      // Window style

	HWND hWndGame = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		cs.x, cs.y, cs.cx, cs.cy, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWndGame, nCmdShow);
	UpdateWindow(hWndGame);

}






