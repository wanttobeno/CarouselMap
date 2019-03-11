// CarouselMap.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CarouselMap.h"
#include "AutoGdiPlus.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

CAutoGdiPlus autoGidplus;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CAROUSELMAP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CAROUSELMAP));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CAROUSELMAP));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CAROUSELMAP);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   // hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW , CW_USEDEFAULT, CW_USEDEFAULT,
	   578, 300, NULL,NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
#include "CarouselPic.h"
#include "MyPainter.h"
#include <gdiplus.h>
#include "NagButtonUI.h"


#define  ZY_BK_COLOR RGB(247, 248, 250)

#define  PIC_MID_WIDTH  302
#define  PIC_MID_HEIGHT 144

#define  PIC_BIG_WIDTH  385
#define  PIC_BIG_HEIGHT 183


#define  ZY_TIME_NEXT_ID 1000
#define  ZY_TIME_NEXT_LONG 1500

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif



int gX = 0;
int gY = 50;

int gLeft1 = 98;
int gLeft2 = 279;

bool m_bMousing = false;

CNagButtonUI g_pBtn1;
CNagButtonUI g_pBtn2;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case  WM_CREATE:
	{
					   // º”‘ÿÕº∆¨
					   CMyPainter* pPainter = CMyPainter::GetInst();
					   wchar_t buf[MAX_PATH] = { 0 };
					   for (int i = 1; i < 6; i++)
					   {
						   wsprintf(buf, L"./Pic/%d.jpg", i);
						   CarouselPic* pPic1 = new CarouselPic;
						   pPic1->LoadPic(buf);
				
						   pPic1->SetLeft((i - 1) * 288);
						   pPainter->AddPic(pPic1);
					   }
					   SetTimer(hWnd, ZY_TIME_NEXT_ID, ZY_TIME_NEXT_LONG, NULL);
	}
		break;
	case WM_TIMER:
	{
					 int nId = wParam;
					 if (nId == ZY_TIME_NEXT_ID)
					 {
						 CMyPainter* painter = CMyPainter::GetInst();
						 painter->MoveToLeft(288);
						 ::InvalidateRect(hWnd, NULL, true);
						 ::UpdateWindow(hWnd);
					 }
	}
		break;
	case  WM_MOUSEMOVE:
	{
						  int x = GET_X_LPARAM(lParam);
						  int y = GET_Y_LPARAM(lParam);
						  bool bRet1 = g_pBtn1.ChangeSate(x, y);
						  bool bRet2 = g_pBtn2.ChangeSate(x, y);
						  if (bRet1 || bRet2)
						  {
							  ::InvalidateRect(hWnd, NULL, true);
							  ::UpdateWindow(hWnd);
						  }
	}
	break;
	case WM_LBUTTONDOWN:
	{
						   int x = GET_X_LPARAM(lParam);
						   int y = GET_Y_LPARAM(lParam);
						   bool bRet1 = g_pBtn1.ChangeSate(x, y);
						   bool bRet2 = g_pBtn2.ChangeSate(x, y);
						   if (bRet1 || bRet2)
						   {
							   ::InvalidateRect(hWnd, NULL, true);
							   ::UpdateWindow(hWnd);
						   }
						   return 0;
	}
	break;
	case WM_LBUTTONUP:
	{
						 m_bMousing = false;
						 // ◊Û∞¥≈•Œª÷√
						 RECT rtLeft = { 20, 90, 80, 150 };
						 // ”“∞¥≈•Œª÷√
						 RECT rtRight = { 480, 90, 540, 150 };
						 int x = GET_X_LPARAM(lParam);
						 int y = GET_Y_LPARAM(lParam);
						 POINT pt;
						 pt.x = x;
						 pt.y = y;
						 if (PtInRect(&rtLeft,pt))
						 {
							 CMyPainter* painter = CMyPainter::GetInst();
							 painter->MoveToRight(288);
							 ::InvalidateRect(hWnd, NULL, true);
							 ::UpdateWindow(hWnd);
						 }
						 else if (PtInRect(&rtRight, pt))
						 {
							 CMyPainter* painter = CMyPainter::GetInst();
							 painter->MoveToLeft(288); 
							 ::InvalidateRect(hWnd, NULL, true);
							 ::UpdateWindow(hWnd);
						 }
						 else
						 {
							 return 0;
						 }
	}
	break;
	case WM_RBUTTONUP:
	{
		m_bMousing = false;

	}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
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
		break;
	case WM_PAINT:
	{
					 hdc = BeginPaint(hWnd, &ps);
					 // TODO: Add any drawing code here...
					 HDC memdc = CreateCompatibleDC(hdc);
					 RECT rect;
					 ::GetClientRect(hWnd, &rect);
					 HBITMAP  hBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
					 ::SelectObject(memdc, hBit);

					 HBRUSH  brBack = (HBRUSH)CreateSolidBrush(ZY_BK_COLOR);
					 FillRect(memdc, &rect, brBack);


					 CMyPainter* pPainter = CMyPainter::GetInst();
					 pPainter->Painter(memdc);

					 Gdiplus::Graphics graphics(memdc);
					 graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
					 // ◊Û∞¥≈•
					 {
						 Gdiplus::RectF bkRect(20, 90, 38, 38);
						 g_pBtn1.SetPos(bkRect);
						 g_pBtn1.Draw(graphics, true);
					 }
					 // ”“∞¥≈•
					 {
						 Gdiplus::RectF bkRect(500, 90, 38, 38);
						 g_pBtn2.SetPos(bkRect);
						 g_pBtn2.Draw(graphics, false);
					 }

			BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, memdc, 0, 0, SRCCOPY);
			DeleteDC(memdc);
			DeleteObject(brBack);
			EndPaint(hWnd, &ps);
	}
		break;
	case WM_ERASEBKGND:
		return 1;
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
