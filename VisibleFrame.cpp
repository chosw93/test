// VisibleFrame.cpp : implementation file
//
#undef _WINDOWS_
#include "stdafx.h"
#include "VitualDesk.h"

#include "VisibleFrame.h"
#include "DefineVariable.h"
#include "ForUsingHook.h"
#include "process.h"
#include "MainFrm.h"
#include <stdio.h>
#include <stdlib.h>

#include <Tlhelp32.h>
#include <ShellAPI.h>
#include <windows.h>

#include <vector>
int				check;

char *szMessage = "Move monitor";
char *szMessage2 = "Select monitor";
char *szMessage3 = "Set the number of virtual monitor";
char *szMessage4 = "The range of numbers can be 2 to 4.";
// mouse 움직임을 통한 화면전환을 구현하기 위해 mouse point를 얻는 변수
POINT point;
POINT pre_point;
POINT menu_point;
POINT menu_point2;
HWND hEdit;

HWND hWnd2;
HWND hWnd3;
HWND hWnd4;

HBRUSH hBrush;

RECT rc2;
RECT rc3;
RECT rc4;


long					positive;
int						wait;
long					negative = 0;

using namespace std;

int Current_desktop_X;
int Current_desktop_X_pre;
int NumofMonitors;

BehindBackgroundIcon helper;

int X_screen_size = 0;
int Y_screen_size = 0;

int				scaledScreenX;
int				scaledScreenY;

int				scaledScreenX_set;
int				scaledScreenY_set;

CVisibleFrame		*pWnd = NULL;
CVisibleFrame		*pWnd2;

#ifdef _DEBUG
//#pragma comment(linker, "?entry:WinMainCRTStartup ?subsystem:console")
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

//LONG TRAY(WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("CONTROL BOX");
LPCTSTR lpszClass2 = TEXT("Initial setting");
LPCTSTR lpszClassMenu1 = TEXT("Menu1");

#define ID_SCRRED 100
#define ID_SCRGREEN 101
#define ID_SCRBLUE 102
HWND hRed;
HWND hremove;
char szname[100];
int Red;
int TempPos;
int TempPos_pre;
int nflag = 0;
float pre_x_point;
float pre_y_point;
int temp123 = 0;
int setting = 0;
int sflag = 0;
int fflag = 0;
char stringPtr[100];
int numofdesktop;

HICON hicon;

//HFONT Font;

LRESULT CALLBACK WndProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	/********** desktop 개수 입력 받기 **********/
	switch (iMessage) {
	case WM_CREATE:
		TRAY_Init(hWnd);
		numofdesktop = 4;
		hEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT, 60, 52, 200, 25, hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Set"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 280, 52, 40, 25, hWnd, (HMENU)0, g_hInst, NULL);
		//Font = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
		return 0;

	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 10, 2, szMessage3, strlen(szMessage3));
		TextOut(hdc, 10, 22, szMessage4, strlen(szMessage4));
		EndPaint(hWnd, &ps);
		break;


	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 0:
			if (sflag == 1) {
				fflag = 1;

				HWND hWnd_dialog;
				WNDCLASS WndClass;
				HINSTANCE hInstance1 = NULL;

				//Main control box....
				WndClass.cbClsExtra = 0;
				WndClass.cbWndExtra = 0;
				WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
				WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
				WndClass.hIcon = WndClass.hIcon = LoadIcon(hInstance1, MAKEINTRESOURCE(IDI_RABBITICO));
				WndClass.hInstance = hInstance1;
				WndClass.lpfnWndProc = WndProc;
				WndClass.lpszClassName = lpszClass;
				WndClass.lpszMenuName = NULL;
				WndClass.style = CS_HREDRAW | CS_VREDRAW;
				RegisterClass(&WndClass);
				while (fflag == 0) {
				}
				switch (numofdesktop) {
				case 2:
					hWnd_dialog = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 200, 180, NULL, (HMENU)NULL, hInstance1, NULL);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof3");
					::ShowWindow(hremove, SW_HIDE);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof4");
					::ShowWindow(hremove, SW_HIDE);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof2");
					::ShowWindow(hremove, SW_SHOW);
					::SetWindowPos(hremove, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
					break;
				case 3:
					hWnd_dialog = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 200, 180, NULL, (HMENU)NULL, hInstance1, NULL);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof2");
					::ShowWindow(hremove, SW_HIDE);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof4");
					::ShowWindow(hremove, SW_HIDE);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof3");
					::ShowWindow(hremove, SW_SHOW);
					::SetWindowPos(hremove, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
					break;
				case 4:
					hWnd_dialog = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 200, 180, NULL, (HMENU)NULL, hInstance1, NULL);
					//hWnd_dialog = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 290, 260, NULL, (HMENU)NULL, hInstance1, NULL);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof2");
					::ShowWindow(hremove, SW_HIDE);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof3");
					::ShowWindow(hremove, SW_HIDE);
					hremove = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof4");
					::ShowWindow(hremove, SW_SHOW);
					::SetWindowPos(hremove, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
					break;
				}

				hremove = ::FindWindow(NULL, "CURRENT_DESKTOP_BLOCK_by_jangcytof2");
				::SetWindowPos(hremove, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

				::ShowWindow(hWnd_dialog, 4);
				//다이얼로그만 끄기
				::SetWindowPos(hWnd_dialog, HWND_NOTOPMOST, X_screen_size - 340, Y_screen_size - 375, X_screen_size - 350 - 80 - 80, Y_screen_size - 100 + 40, SWP_NOZORDER);
				::ShowWindow(hWnd, SW_HIDE);
				//DestroyWindow(hWnd);
			}

			else if (sflag == 0) {
				MessageBox(hWnd, TEXT("You have entered the wrong number."), TEXT("Warning"), MB_OK);
			}
			break;

		case ID_EDIT:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				GetWindowText(hEdit, stringPtr, 128);
				numofdesktop = atoi(stringPtr);
				if (numofdesktop >= 2 && numofdesktop <= 4)	sflag = 1;
				else sflag = 0;
				TRACE("***************caseEN_CHANGE*******************데스크톱 개수  = %d\n", numofdesktop);
				break;
			}
		}
		break;


	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = scaledScreenX_set;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = scaledScreenY_set;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = scaledScreenX_set;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = scaledScreenY_set;

	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			TRACE("TEST\n");
		}
		break;

	case WM_DESTROY:
		OnDestroyTray();//Clean Tray related
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (numofdesktop == 4) {
		//TRACE("wait = %d\n", wait);
		//TRACE("WndProce 동작---------------------------------------------------\n");

		DEVMODE mode;
		::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);

		int m_nScreenX = mode.dmPelsWidth;
		int start_pos = 0;
		int min_range = 0;
		int max_range = m_nScreenX * 3;
		int min_step = m_nScreenX / 80;
		int max_step = m_nScreenX / 40;

		switch (iMessage)
		{
		case WM_CREATE:
			TRAY_Init(hWnd);
			CreateWindow(TEXT("button1"), TEXT("Program End"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 135, 180, 20, hWnd, (HMENU)0, g_hInst, NULL);
			CreateWindow(TEXT("button2"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 7, 35, 35, 35, hWnd, (HMENU)1, g_hInst, NULL);
			CreateWindow(TEXT("button3"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 45 + 24 - 20 + 7, 35, 35, 35, hWnd, (HMENU)2, g_hInst, NULL);
			CreateWindow(TEXT("button4"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 69 + 69 - 20 - 20 + 7, 35, 35, 35, hWnd, (HMENU)3, g_hInst, NULL);
			CreateWindow(TEXT("button5"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 69 + 69 + 69 - 20 - 20 - 20 + 7, 35, 35, 35, hWnd, (HMENU)4, g_hInst, NULL);

			hRed = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 30, 105, 160, 20, hWnd, (HMENU)ID_SCRRED, g_hInst, NULL);
			SetScrollRange(hRed, SB_CTL, min_range, max_range, TRUE);
			SetScrollPos(hRed, SB_CTL, start_pos, TRUE);
			return 0;

		//case WM_CTLCOLORSTATIC:
		//	if (lParam == (LPARAM)hWnd)
		//	{
		//		if (hBrush) { DeleteObject(hBrush); hBrush = NULL; }
		//		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		//		SetBkColor((HDC)wParam, RGB(0, 255, 0));     // 텍스트의 배경색을 컨트롤의 색과 일치시킵니다.
		//		SetTextColor((HDC)wParam, RGB(255, 255, 255));     // 텍스트의 폰트 색을 흰색으로 바꿉니다.
		//		return (LRESULT)hBrush;
		//	}

		case WM_GETMINMAXINFO:
			((MINMAXINFO*)lParam)->ptMaxTrackSize.x = scaledScreenX;
			((MINMAXINFO*)lParam)->ptMaxTrackSize.y = scaledScreenY;
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = scaledScreenX;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = scaledScreenY;
			break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint(hWnd, &ps);
			SetTextColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, scaledScreenX / 2 - 55, 80, szMessage, strlen(szMessage));
			TextOut(hdc, scaledScreenX / 2 - 60, 5, szMessage2, strlen(szMessage2));
			EndPaint(hWnd, &ps);
			break;

		case WM_NOTIFYICONTRAY:
			OnNotifyTray(lParam); // Manages message from tray
			return TRUE;

		case WM_SIZE:
			OnSizeTray(wParam); // Minimize/Restore to/from tray
			break;

		case WM_COMMAND:
			if (OnCommandTrayMenu(wParam)) break;
			switch (LOWORD(wParam))
			{

			case 0:
			{
				MessageBox(hWnd, TEXT("Vitual desktop program will be terminated"), TEXT("CONTROL BOX"), MB_OK);
				OnDestroyTray();//Clean Tray related
				PostQuitMessage(0);
				g_pVisibleWnd->DesktopPosInit();

				PROCESSENTRY32 pEntry;
				HANDLE hSnapShot;
				DWORD dwSize = 250;
				BOOL bCrrent = FALSE;

				// 시스템 종료
				hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

				pEntry.dwSize = sizeof(pEntry);
				// 실행중인 프로세스들의 첫번재 정보를 가져온다.
				Process32First(hSnapShot, &pEntry);

				// Tool이 실행중인지 확인
				while (1)
				{
					// 다음번 프로세스의 정보를 가져온다.
					BOOL hRes = Process32Next(hSnapShot, &pEntry);

					if (hRes == FALSE)
						break;
					if (!strncmp(pEntry.szExeFile, "Panorama virtual monitor.exe", 30))
					{
						bCrrent = TRUE;
					}
					if (bCrrent)
					{
						HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pEntry.th32ProcessID);
						if (hProcess)
						{
							if (TerminateProcess(hProcess, 0))
							{
								unsigned long nCode; //프로세스 종료 상태
								GetExitCodeProcess(hProcess, &nCode);
							}
							CloseHandle(hProcess);
						}
						break;
					}
				}
			}
			break;

			case 1:
				TempPos = 0;
				::SetScrollPos(hRed, SB_CTL, 0, true);
				break;
			case 2:
				TempPos = m_nScreenX;
				::SetScrollPos(hRed, SB_CTL, m_nScreenX, true);
				break;
			case 3:
				TempPos = m_nScreenX * 2;
				::SetScrollPos(hRed, SB_CTL, m_nScreenX * 2, true);
				break;
			case 4:
				if (NumofMonitors == 1) {
					TempPos = (m_nScreenX * 3);
					::SetScrollPos(hRed, SB_CTL, (m_nScreenX * 3), true);
				}
				else if (NumofMonitors == 2) {
					MessageBox(hWnd, TEXT("The range is exceeded"), TEXT("Warning"), MB_OK);
				}
				break;
			}
			return 0;

		case WM_RBUTTONDOWN: {
			TRAY_Menu_Show();
		}break;

		case WM_HSCROLL:
			if ((HWND)lParam == hRed) { //TempPos = Red;
				switch (LOWORD(wParam)) {
					if (wait == 0) {
				case SB_LINELEFT:
					TempPos_pre = TempPos;
					TempPos = max(min_range, TempPos - (2 * min_step));
					break;
				case SB_LINERIGHT:
					if (NumofMonitors == 1) {
						TempPos_pre = TempPos;
						TempPos = min(max_range, TempPos + (2 * min_step));
					}
					else if (NumofMonitors == 2) {
						TempPos_pre = TempPos;
						TempPos = min(max_range - m_nScreenX, TempPos + (2 * min_step));
					}
					break;

				case SB_PAGELEFT:

					TempPos_pre = TempPos;

					TempPos = max(min_range, TempPos - (2 * max_step));
					TRACE("TempPos 업데이트 안에서 [TempPos] = %d, [TempPos_pre] = %d, [변화량] = %d\n", TempPos, TempPos_pre, TempPos - TempPos_pre);
					//if (g_pVisibleWnd != NULL)
					//	g_pVisibleWnd->MoveDesktopTo(TempPos / 2, TempPos_pre / 2);

					break;

				case SB_PAGERIGHT:
					if (NumofMonitors == 1) {
						TempPos_pre = TempPos;
						TempPos = min(max_range, TempPos + (2 * max_step));
					}
					else if (NumofMonitors == 2) {
						TempPos_pre = TempPos;
						TempPos = min(max_range - m_nScreenX, TempPos + (2 * max_step));
					}
					break;

				case SB_THUMBTRACK:
					if (NumofMonitors == 1) {
						TempPos = min(max_range, TempPos + (2 * max_step));

						temp123 = 0;
						TempPos_pre = TempPos;
						TempPos = HIWORD(wParam);
						TRACE("[before TempPos] = %d \n", TempPos);
						while ((TempPos % max_step) != 0) {
							TempPos = TempPos - 1;
							temp123++;
						}
						TRACE("[TempPos 변화] = %d \n", temp123);
						TRACE("[after TempPos] = %d \n", TempPos);
						SetScrollPos(hRed, SB_CTL, TempPos, true);
						break;
						wait = 1;
					}
					else if (NumofMonitors == 2) {
						temp123 = 0;
						TempPos_pre = TempPos;
						TempPos = HIWORD(wParam);
						TRACE("[before TempPos] = %d \n", TempPos);
						while ((TempPos % max_step) != 0) {
							TempPos = TempPos - 1;
							temp123++;
						}
						TRACE("[TempPos 변화] = %d \n", temp123);
						TRACE("[after TempPos] = %d \n", TempPos);
						SetScrollPos(hRed, SB_CTL, TempPos, true);

						/*			if (g_pVisibleWnd != NULL)
						g_pVisibleWnd->MoveDesktopTo(TempPos / 2, TempPos_pre / 2);*/
						TempPos = min(max_range - m_nScreenX, TempPos + (2 * max_step));
						break;
						wait = 1;
					}



					}
				}

				if ((HWND)lParam == hRed) Red = TempPos;
				SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			return 0;


		case WM_DESTROY:
			g_pVisibleWnd->DesktopPosInit();
			OnDestroyTray();//Clean Tray related
			PostQuitMessage(0);
			//MessageBox(hWnd,TEXT("Vitual desktop program will be terminated"), TEXT("button"), MB_OK);
			PROCESSENTRY32 pEntry;
			HANDLE hSnapShot;
			DWORD dwSize = 250;
			BOOL bCrrent = FALSE;

			// 시스템 종료
			hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
			pEntry.dwSize = sizeof(pEntry);

			// 실행중인 프로세스들의 첫번재 정보를 가져온다.
			Process32First(hSnapShot, &pEntry);

			// Tool이 실행중인지 확인
			while (1)
			{
				// 다음번 프로세스의 정보를 가져온다.
				BOOL hRes = Process32Next(hSnapShot, &pEntry);

				if (hRes == FALSE)
					break;
				if (!strncmp(pEntry.szExeFile, "Panorama virtual monitor.exe", 30))
				{
					bCrrent = TRUE;
				}
				if (bCrrent)
				{
					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pEntry.th32ProcessID);
					if (hProcess)
					{
						if (TerminateProcess(hProcess, 0))
						{
							unsigned long nCode; //프로세스 종료 상태
							GetExitCodeProcess(hProcess, &nCode);
						}
						CloseHandle(hProcess);
					}
					break;
				}
			}
			return 0;
		}
	}

	else if (numofdesktop == 2) {
		//TRACE("wait = %d\n", wait);
		//TRACE("WndProce 동작---------------------------------------------------\n");

		DEVMODE mode;
		::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);
		int m_nScreenX = mode.dmPelsWidth;
		int start_pos = 0;
		int min_range = 0;
		int max_range = m_nScreenX * (2 - 1);
		int min_step = m_nScreenX / 80;
		int max_step = m_nScreenX / 40;

		switch (iMessage)
		{
		case WM_CREATE:
			TRAY_Init(hWnd);
			CreateWindow(TEXT("button"), TEXT("Program End"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 135, 180, 20, hWnd, (HMENU)0, g_hInst, NULL);
			CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 50, 35, 35, 35, hWnd, (HMENU)1, g_hInst, NULL);
			CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 20 + 40 + 45 + 24 - 20, 35, 35, 35, hWnd, (HMENU)2, g_hInst, NULL);

			hRed = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 30, 105, 160, 20, hWnd, (HMENU)ID_SCRRED, g_hInst, NULL);
			SetScrollRange(hRed, SB_CTL, min_range, max_range, TRUE);
			SetScrollPos(hRed, SB_CTL, start_pos, TRUE);
			return 0;

		case WM_GETMINMAXINFO:
			((MINMAXINFO*)lParam)->ptMaxTrackSize.x = scaledScreenX;
			((MINMAXINFO*)lParam)->ptMaxTrackSize.y = scaledScreenY;
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = scaledScreenX;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = scaledScreenY;
			break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint(hWnd, &ps);
			SetTextColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, scaledScreenX / 2 - 55, 80, szMessage, strlen(szMessage));
			TextOut(hdc, scaledScreenX / 2 - 60, 5, szMessage2, strlen(szMessage2));
			EndPaint(hWnd, &ps);
			break;

		case WM_NOTIFYICONTRAY:
			OnNotifyTray(lParam); // Manages message from tray
			return TRUE;

		case WM_SIZE:
			OnSizeTray(wParam); // Minimize/Restore to/from tray
			break;

		case WM_COMMAND:
			if (OnCommandTrayMenu(wParam)) break;
			switch (LOWORD(wParam))
			{

			case 0:
			{
				MessageBox(hWnd, TEXT("Vitual desktop program will be terminated"), TEXT("CONTROL BOX"), MB_OK);
				OnDestroyTray();//Clean Tray related
				PostQuitMessage(0);
				g_pVisibleWnd->DesktopPosInit();

				PROCESSENTRY32 pEntry;
				HANDLE hSnapShot;
				DWORD dwSize = 250;
				BOOL bCrrent = FALSE;

				// 시스템 종료
				hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

				pEntry.dwSize = sizeof(pEntry);
				// 실행중인 프로세스들의 첫번재 정보를 가져온다.
				Process32First(hSnapShot, &pEntry);

				// Tool이 실행중인지 확인
				while (1)
				{
					// 다음번 프로세스의 정보를 가져온다.
					BOOL hRes = Process32Next(hSnapShot, &pEntry);

					if (hRes == FALSE)
						break;
					if (!strncmp(pEntry.szExeFile, "Virtual Workspace.exe", 15))
					{
						bCrrent = TRUE;
					}
					if (bCrrent)
					{
						HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pEntry.th32ProcessID);
						if (hProcess)
						{
							if (TerminateProcess(hProcess, 0))
							{
								unsigned long nCode; //프로세스 종료 상태
								GetExitCodeProcess(hProcess, &nCode);
							}
							CloseHandle(hProcess);
						}
						break;
					}
				}
			}
			break;
			case 1:
				TempPos = 0;
				::SetScrollPos(hRed, SB_CTL, 0, true);
				break;
			case 2:
				if (NumofMonitors == 1) {
					TempPos = m_nScreenX;
					::SetScrollPos(hRed, SB_CTL, m_nScreenX, true);
				}
				else if (NumofMonitors == 2) {
					MessageBox(hWnd, TEXT("The range is exceeded"), TEXT("Warning"), MB_OK);
				}

				break;
			}
			return 0;

		case WM_RBUTTONDOWN: {
			TRAY_Menu_Show();
		}break;

		case WM_LBUTTONDBLCLK: {
			TRAY_Menu_Show();
		}break;

		case WM_HSCROLL:
			if ((HWND)lParam == hRed) { //TempPos = Red;
				switch (LOWORD(wParam)) {
					if (wait == 0) {
				case SB_LINELEFT:
					TempPos_pre = TempPos;
					TempPos = max(min_range, TempPos - (2 * min_step));
					break;

				case SB_LINERIGHT:
					if (NumofMonitors == 1) {
						TempPos_pre = TempPos;
						TempPos = min(max_range, TempPos + (2 * min_step));
					}
					else if (NumofMonitors == 2) {
						MessageBox(hWnd, TEXT("The range is exceeded"), TEXT("Warning"), MB_OK);
					}
					break;

				case SB_PAGELEFT:
					TempPos_pre = TempPos;
					TempPos = max(min_range, TempPos - (2 * max_step));
					break;

				case SB_PAGERIGHT:
					if (NumofMonitors == 1) {
						TempPos_pre = TempPos;
						TempPos = min(max_range, TempPos + (2 * max_step));
					}
					else if (NumofMonitors == 2) {
						MessageBox(hWnd, TEXT("The range is exceeded"), TEXT("Warning"), MB_OK);
					}
					break;

				case SB_THUMBTRACK:
					if (NumofMonitors == 1) {
						temp123 = 0;
						TempPos_pre = TempPos;
						TempPos = HIWORD(wParam);
						TRACE("[before TempPos] = %d \n", TempPos);
						while ((TempPos % max_step) != 0) {
							TempPos = TempPos - 1;
							temp123++;
						}
						TRACE("[TempPos 변화] = %d \n", temp123);
						TRACE("[after TempPos] = %d \n", TempPos);
						SetScrollPos(hRed, SB_CTL, TempPos, true);
					}
					else if (NumofMonitors == 2) {
						MessageBox(hWnd, TEXT("The range is exceeded"), TEXT("Warning"), MB_OK);
					}
					break;
					wait = 1;
					}
				}

				if ((HWND)lParam == hRed) Red = TempPos;
				SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			return 0;


		case WM_DESTROY:
			g_pVisibleWnd->DesktopPosInit();
			OnDestroyTray();//Clean Tray related
			PostQuitMessage(0);
			//MessageBox(hWnd,TEXT("Vitual desktop program will be terminated"), TEXT("button"), MB_OK);
			PROCESSENTRY32 pEntry;
			HANDLE hSnapShot;
			DWORD dwSize = 250;
			BOOL bCrrent = FALSE;

			// 시스템 종료
			hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
			pEntry.dwSize = sizeof(pEntry);

			// 실행중인 프로세스들의 첫번재 정보를 가져온다.
			Process32First(hSnapShot, &pEntry);

			// Tool이 실행중인지 확인
			while (1)
			{
				// 다음번 프로세스의 정보를 가져온다.
				BOOL hRes = Process32Next(hSnapShot, &pEntry);

				if (hRes == FALSE)
					break;
				if (!strncmp(pEntry.szExeFile, "Panorama virtual monitor.exe", 30))
				{
					bCrrent = TRUE;
				}
				if (bCrrent)
				{
					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pEntry.th32ProcessID);
					if (hProcess)
					{
						if (TerminateProcess(hProcess, 0))
						{
							unsigned long nCode; //프로세스 종료 상태
							GetExitCodeProcess(hProcess, &nCode);
						}
						CloseHandle(hProcess);
					}
					break;
				}

			}
			return 0;
		}
	}

	else if (numofdesktop == 3) {
		//TRACE("wait = %d\n", wait);
		//TRACE("WndProce 동작---------------------------------------------------\n");

		DEVMODE mode;
		::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);

		int m_nScreenX = mode.dmPelsWidth;
		int start_pos = 0;
		int min_range = 0;
		int max_range = m_nScreenX * (3 - 1);
		int min_step = m_nScreenX / 80;
		int max_step = m_nScreenX / 40;

		switch (iMessage)
		{
		case WM_CREATE:
			TRAY_Init(hWnd);
			CreateWindow(TEXT("button"), TEXT("Program End"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 135, 180, 20, hWnd, (HMENU)0, g_hInst, NULL);
			CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 20, 35, 35, 35, hWnd, (HMENU)1, g_hInst, NULL);
			CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 20 + 10 + 45 + 24 - 20, 35, 35, 35, hWnd, (HMENU)2, g_hInst, NULL);
			CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 12 + 69 + 10 + 10 + 20 + 69 - 20 - 20, 35, 35, 35, hWnd, (HMENU)3, g_hInst, NULL);

			hRed = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 30, 105, 160, 20, hWnd, (HMENU)ID_SCRRED, g_hInst, NULL);
			SetScrollRange(hRed, SB_CTL, min_range, max_range, TRUE);
			SetScrollPos(hRed, SB_CTL, start_pos, TRUE);
			return 0;

		case WM_GETMINMAXINFO:
			((MINMAXINFO*)lParam)->ptMaxTrackSize.x = scaledScreenX;
			((MINMAXINFO*)lParam)->ptMaxTrackSize.y = scaledScreenY;
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = scaledScreenX;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = scaledScreenY;
			break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint(hWnd, &ps);
			SetTextColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, scaledScreenX / 2 - 55, 80, szMessage, strlen(szMessage));
			TextOut(hdc, scaledScreenX / 2 - 60, 5, szMessage2, strlen(szMessage2));
			EndPaint(hWnd, &ps);
			break;

		case WM_NOTIFYICONTRAY:
			OnNotifyTray(lParam); // Manages message from tray
			return TRUE;

		case WM_SIZE:
			OnSizeTray(wParam); // Minimize/Restore to/from tray
			break;

		case WM_COMMAND:
			if (OnCommandTrayMenu(wParam)) break;
			switch (LOWORD(wParam))
			{

			case 0:
			{
				MessageBox(hWnd, TEXT("Vitual desktop program will be terminated"), TEXT("CONTROL BOX"), MB_OK);
				OnDestroyTray();//Clean Tray related
				PostQuitMessage(0);
				g_pVisibleWnd->DesktopPosInit();

				PROCESSENTRY32 pEntry;
				HANDLE hSnapShot;
				DWORD dwSize = 250;
				BOOL bCrrent = FALSE;

				// 시스템 종료
				hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

				pEntry.dwSize = sizeof(pEntry);
				// 실행중인 프로세스들의 첫번재 정보를 가져온다.
				Process32First(hSnapShot, &pEntry);

				// Tool이 실행중인지 확인
				while (1)
				{
					// 다음번 프로세스의 정보를 가져온다.
					BOOL hRes = Process32Next(hSnapShot, &pEntry);

					if (hRes == FALSE)
						break;
					if (!strncmp(pEntry.szExeFile, "Virtual Workspace.exe", 15))
					{
						bCrrent = TRUE;
					}
					if (bCrrent)
					{
						HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pEntry.th32ProcessID);
						if (hProcess)
						{
							if (TerminateProcess(hProcess, 0))
							{
								unsigned long nCode; //프로세스 종료 상태
								GetExitCodeProcess(hProcess, &nCode);
							}
							CloseHandle(hProcess);
						}
						break;
					}
				}
			}
			break;
			case 1:
				TempPos = 0;
				::SetScrollPos(hRed, SB_CTL, 0, true);
				break;
			case 2:
				TempPos = m_nScreenX;
				::SetScrollPos(hRed, SB_CTL, m_nScreenX, true);
				break;
			case 3:
				if (NumofMonitors == 1) {
					TempPos = m_nScreenX * 2;
					::SetScrollPos(hRed, SB_CTL, m_nScreenX * 2, true);
				}
				else if (NumofMonitors == 2) {
					MessageBox(hWnd, TEXT("The range is exceeded"), TEXT("Warning"), MB_OK);
				}
				break;
			}
			return 0;

		case WM_RBUTTONDOWN: {
			TRAY_Menu_Show();
		}break;

		case WM_LBUTTONDBLCLK: {
			TRAY_Menu_Show();
		}break;

		case WM_HSCROLL:
			if ((HWND)lParam == hRed) { //TempPos = Red;
				switch (LOWORD(wParam)) {
					if (wait == 0) {
				case SB_LINELEFT:

					TempPos_pre = TempPos;

					TempPos = max(min_range, TempPos - (2 * min_step));
					TRACE("TempPos 업데이트 안에서 [TempPos] = %d, [TempPos_pre] = %d \n", TempPos, TempPos_pre);

					//g_pVisibleWnd->MoveDesktopTo(m_nScreenX, 0);

					/*			if (g_pVisibleWnd != NULL)
					g_pVisibleWnd->MoveDesktopTo(TempPos/2, TempPos_pre/2);
					*/
					break;
				case SB_LINERIGHT:
					if (NumofMonitors == 1) {
						TempPos_pre = TempPos;
						TempPos = min(max_range, TempPos + (2 * min_step));
					}
					else if (NumofMonitors == 2) {
						TempPos_pre = TempPos;
						TempPos = min(max_range - m_nScreenX, TempPos + (2 * min_step));
					}
					break;

				case SB_PAGELEFT:
					TempPos_pre = TempPos;
					TempPos = max(min_range, TempPos - (2 * max_step));
					break;

				case SB_PAGERIGHT:
					if (NumofMonitors == 1) {
						TempPos_pre = TempPos;
						TempPos = min(max_range, TempPos + (2 * max_step));
					}
					else if (NumofMonitors == 2) {
						TempPos_pre = TempPos;
						TempPos = min(max_range - m_nScreenX, TempPos + (2 * max_step));
					}
					break;

				case SB_THUMBTRACK:
					if (NumofMonitors == 1) {
						temp123 = 0;
						TempPos_pre = TempPos;
						TempPos = HIWORD(wParam);
						TRACE("[before TempPos] = %d \n", TempPos);
						while ((TempPos % max_step) != 0) {
							TempPos = TempPos - 1;
							temp123++;
						}
						TRACE("[TempPos 변화] = %d \n", temp123);
						TRACE("[after TempPos] = %d \n", TempPos);
						SetScrollPos(hRed, SB_CTL, TempPos, true);
					}
					else if (NumofMonitors == 2) {
						temp123 = 0;
						TempPos_pre = TempPos;
						TempPos = HIWORD(wParam);
						TRACE("[before TempPos] = %d \n", TempPos);
						while ((TempPos % max_step) != 0) {
							TempPos = TempPos - 1;
							temp123++;
						}
						TRACE("[TempPos 변화] = %d \n", temp123);
						TRACE("[after TempPos] = %d \n", TempPos);
						SetScrollPos(hRed, SB_CTL, TempPos, true);
						TempPos = min(max_range - m_nScreenX, TempPos + (2 * max_step));
					}
					break;

					wait = 1;
					}
				}

				if ((HWND)lParam == hRed) Red = TempPos;
				SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			return 0;


		case WM_DESTROY:
			g_pVisibleWnd->DesktopPosInit();
			OnDestroyTray();//Clean Tray related
			PostQuitMessage(0);
			//MessageBox(hWnd,TEXT("Vitual desktop program will be terminated"), TEXT("button"), MB_OK);
			PROCESSENTRY32 pEntry;
			HANDLE hSnapShot;
			DWORD dwSize = 250;
			BOOL bCrrent = FALSE;

			// 시스템 종료
			hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
			pEntry.dwSize = sizeof(pEntry);

			// 실행중인 프로세스들의 첫번재 정보를 가져온다.
			Process32First(hSnapShot, &pEntry);

			// Tool이 실행중인지 확인
			while (1)
			{
				// 다음번 프로세스의 정보를 가져온다.
				BOOL hRes = Process32Next(hSnapShot, &pEntry);

				if (hRes == FALSE)
					break;
				if (!strncmp(pEntry.szExeFile, "Virtual Workspace.exe", 15))
				{
					bCrrent = TRUE;
				}
				if (bCrrent)
				{
					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pEntry.th32ProcessID);
					if (hProcess)
					{
						if (TerminateProcess(hProcess, 0))
						{
							unsigned long nCode; //프로세스 종료 상태
							GetExitCodeProcess(hProcess, &nCode);
						}
						CloseHandle(hProcess);
					}
					break;
				}

			}
			return 0;
		}
	}


	else {
		//TRACE("********잘못된 desktop 개수**************\n");
		//TRACE("***********************************데스크톱 개수  = %d\n", numofdesktop);
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/////////////////////////////////////////////////////////////////////////////
// CVisibleFrame
IMPLEMENT_DYNCREATE(CVisibleFrame, CFrameWnd)

void CVisibleFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	// 여기에 윈도우 갱신코드가 들어가야 합니다. 통상 아래와 같은 코드가 들어가겠죠.. ^^; 
	// Invalidate(); 

	CVisibleFrame::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CVisibleFrame::ThreadFunc(void *lParam)
{

	int temp_point = 0;
	CVisibleFrame			*pThisClass;
	pThisClass = (CVisibleFrame *)lParam;

	char szWindowName[100];
	HDC hdc;
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	DEVMODE mode;
	::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);

	int m_nScreenX = mode.dmPelsWidth;
	int m_nScreenY = mode.dmPelsHeight;
	int min_range = 0;
	int max_range = m_nScreenX * (numofdesktop - 1);
	int min_step = m_nScreenX / 80;
	int max_step = m_nScreenX / 40;

	///////////////////////////////////////// control box ////////////////////////////////////
	while (pThisClass->m_bSetEndThread == FALSE) {
		::Sleep(1);
		if ((GetAsyncKeyState(VK_LWIN) & 0x8000) && (GetAsyncKeyState(VK_TAB) & 0x8000)) {
			temp123++;
			TRACE("%d 확인하기~~~~~~~~~~~~~\n", temp123);
		}

		temp_point = 0;
		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000)) {
			GetCursorPos(&pre_point);
			::Sleep(1);
			GetCursorPos(&point);
			//좌로 이동
			if ((point.x - pre_point.x) > 0) {
				if (NumofMonitors == 1) {
					if (TempPos < min_range) {
						TempPos = min_range;
						::SetScrollPos(hRed, SB_CTL, min_range, true);
					}
					else if (TempPos > max_range) {
						TempPos = max_range;
						::SetScrollPos(hRed, SB_CTL, max_range, true);
					}
					else {
						TempPos = max(min_range, TempPos - (max_step));
						::SetScrollPos(hRed, SB_CTL, TempPos, true);
					}
				}
				else if (NumofMonitors == 2) {
					if (numofdesktop == 2) {
						//TRACE("NOTHING\n");
					}
					else if (numofdesktop == 3) {
						if (TempPos < min_range) {
							TempPos = min_range;
							::SetScrollPos(hRed, SB_CTL, min_range, true);
						}
						else if (TempPos > max_range - m_nScreenX - m_nScreenX) {
							TempPos = max_range - m_nScreenX - m_nScreenX;
							::SetScrollPos(hRed, SB_CTL, max_range - m_nScreenX - m_nScreenX, true);
						}
						else {
							TempPos = max(min_range, TempPos - (max_step));
							::SetScrollPos(hRed, SB_CTL, TempPos, true);
						}
					}
					else if (numofdesktop == 4) {
						if (TempPos < min_range) {
							TempPos = min_range;
							::SetScrollPos(hRed, SB_CTL, min_range, true);
						}
						else if (TempPos > max_range - m_nScreenX) {
							TempPos = max_range - m_nScreenX;
							::SetScrollPos(hRed, SB_CTL, max_range - m_nScreenX, true);
						}
						else {
							TempPos = max(min_range, TempPos - (max_step));
							::SetScrollPos(hRed, SB_CTL, TempPos, true);
						}
					}

				}
			}

			//우로이동
			else if ((point.x - pre_point.x) < 0) {
				if (NumofMonitors == 1) {
					if (TempPos < min_range) {
						TempPos = min_range;
						::SetScrollPos(hRed, SB_CTL, TempPos, true);
					}
					else if (TempPos > max_range) {
						TempPos = max_range;
						::SetScrollPos(hRed, SB_CTL, max_range, true);
					}
					else {
						TempPos = min(max_range, TempPos + (max_step));
						::SetScrollPos(hRed, SB_CTL, TempPos, true);
					}
				}
				else if (NumofMonitors == 2) {
					if (numofdesktop == 2) {
						//TRACE("NOTHING\n");
					}
					else if (numofdesktop == 3) {
						if (TempPos < min_range) {
							TempPos = min_range;
							::SetScrollPos(hRed, SB_CTL, TempPos, true);
						}
						else if (TempPos > max_range - m_nScreenX - m_nScreenX) {
							TempPos = max_range - m_nScreenX - m_nScreenX;
							::SetScrollPos(hRed, SB_CTL, max_range - m_nScreenX - m_nScreenX, true);
						}
						else {
							TempPos = min(max_range - m_nScreenX - m_nScreenX, TempPos + (max_step));
							::SetScrollPos(hRed, SB_CTL, TempPos, true);
						}
					}
					else if (numofdesktop == 4) {
						if (TempPos < min_range) {
							TempPos = min_range;
							::SetScrollPos(hRed, SB_CTL, TempPos, true);
						}
						else if (TempPos > max_range - m_nScreenX) {
							TempPos = max_range - m_nScreenX;
							::SetScrollPos(hRed, SB_CTL, max_range - m_nScreenX, true);
						}
						else {
							TempPos = min(max_range - m_nScreenX, TempPos + (max_step));
							::SetScrollPos(hRed, SB_CTL, TempPos, true);
						}
					}
				}
			}
		}
		if (NumofMonitors == 1) {
			if (numofdesktop == 2) {
				if (((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) || (GetAsyncKeyState(0X31) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = 0;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, 0, true);
				}
				if (((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) || (GetAsyncKeyState(0X32) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, X_screen_size, true);
				}
			}

			else if (numofdesktop == 3) {
				if (((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) || (GetAsyncKeyState(0X31) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = 0;
					///TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, 0, true);
				}
				if (((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) || (GetAsyncKeyState(0X32) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, X_screen_size, true);
				}

				if (((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) || (GetAsyncKeyState(0X33) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size * 2;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, X_screen_size * 2, true);
				}
			}

			else if (numofdesktop == 4) {
				if (((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) || (GetAsyncKeyState(0X31) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = 0;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, 0, true);
				}
				if (((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) || (GetAsyncKeyState(0X32) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, X_screen_size, true);
				}

				if (((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) || (GetAsyncKeyState(0X33) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size * 2;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, X_screen_size * 2, true);
				}
				if (((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) || (GetAsyncKeyState(0X34) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size * 3;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, (X_screen_size * 3), true);
				}
			}
		}

		else if (NumofMonitors == 2) {
			if (numofdesktop == 2) {
				if (((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) || (GetAsyncKeyState(0X31) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = 0;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, 0, true);
				}
			}

			else if (numofdesktop == 3) {
				if (((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) || (GetAsyncKeyState(0X31) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = 0;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, 0, true);
				}
				if (((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) || (GetAsyncKeyState(0X32) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, X_screen_size, true);
				}
			}

			else if (numofdesktop == 4) {
				if (((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) || (GetAsyncKeyState(0X31) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = 0;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, 0, true);
				}
				if (((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) || (GetAsyncKeyState(0X32) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, X_screen_size, true);
				}

				if (((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) || (GetAsyncKeyState(0X33) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
					TempPos = X_screen_size * 2;
					//TRACE("현재 위치 = %d\n", TempPos);
					::SetScrollPos(hRed, SB_CTL, X_screen_size * 2, true);
				}
			}
		}

		/*여기가 잘 되는지 모르겄다. 미니 맵이 BLOCK 사이즈 밖으로 밀리지 않게... 나가게 되면 허용할 수 있는 최대 범위로 이동시켜버림.*/
		hWnd2 = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof2");
		hWnd3 = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof3");
		hWnd4 = ::FindWindow(NULL, "DESKTOP_MAP_by_jangcytof4");
		::GetWindowRect(hWnd2, &rc2);
		::GetWindowRect(hWnd3, &rc3);
		::GetWindowRect(hWnd4, &rc4);
		if (hWnd2 != NULL) {
			if (rc2.left >= X_screen_size - 350)
				::SetWindowPos(hWnd2, HWND_NOTOPMOST, X_screen_size - 350, Y_screen_size - 100, X_screen_size - 350 - 80 - 80, Y_screen_size - 100 + 40, SWP_NOZORDER);
			if (rc2.left <= X_screen_size - 350 - 80) {
				::SetWindowPos(hWnd2, HWND_NOTOPMOST, X_screen_size - 350 - 80, Y_screen_size - 100, X_screen_size - 350 - 80 - 80 - 80, Y_screen_size - 100 + 40, SWP_NOZORDER);
			}
		}
		else if (hWnd3 != NULL) {
			if (rc3.left >= X_screen_size - 350)
				::SetWindowPos(hWnd3, HWND_NOTOPMOST, X_screen_size - 350, Y_screen_size - 100, X_screen_size - 350 - 80 - 80, Y_screen_size - 100 + 40, SWP_NOZORDER);
			if (rc3.left <= X_screen_size - 350 - 80 - 80) {
				::SetWindowPos(hWnd3, HWND_NOTOPMOST, X_screen_size - 350 - 80 - 80, Y_screen_size - 100, X_screen_size - 350 - 80 - 80 - 80 - 80, Y_screen_size - 100 + 40, SWP_NOZORDER);
			}
		}
		else if (hWnd4 != NULL) {
			if (rc4.left >= X_screen_size - 350)
				::SetWindowPos(hWnd4, HWND_NOTOPMOST, X_screen_size - 350, Y_screen_size - 100, X_screen_size - 350 - 80 - 80 - 80, Y_screen_size - 100 + 40, SWP_NOZORDER);
			if (rc4.left <= X_screen_size - 350 - 80 - 80 - 80) {
				::SetWindowPos(hWnd4, HWND_NOTOPMOST, X_screen_size - 350 - 80 - 80 - 80, Y_screen_size - 100, X_screen_size - 350 - 80 - 80 - 80 - 80 - 80 - 80, Y_screen_size - 100 + 40, SWP_NOZORDER);
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//TRACE("Thread 동작---------------------------------------------------\n");
		if ((TempPos < 0) || (TempPos > X_screen_size * (numofdesktop - 1))) {
			Current_desktop_X_pre = Current_desktop_X;
			Current_desktop_X = Current_desktop_X;
		}
		else
		{
			Current_desktop_X_pre = Current_desktop_X;
			Current_desktop_X = TempPos;
		}

		if ((Current_desktop_X < 0) || (Current_desktop_X > X_screen_size * (numofdesktop - 1)) || (Current_desktop_X_pre < 0) || (Current_desktop_X_pre > X_screen_size * (numofdesktop - 1))) {
			TRACE("============================ RANGE ERROR ===========================\n");
			pThisClass->MoveDesktopTo(Current_desktop_X_pre, Current_desktop_X_pre); //
		}
		else
		{
			if (Current_desktop_X != Current_desktop_X_pre)
				pThisClass->MoveDesktopTo(Current_desktop_X, Current_desktop_X_pre); //
			Current_desktop_X_pre = Current_desktop_X;
			//TRACE("* wait 0으로 바뀌기 바로 전[wait] = %d\n", wait);
			wait = 0;
			//TRACE("* wait 0으로 바뀌고 바로 후[wait] = %d\n", wait);
		}

		pThisClass->m_bIsEndThread = TRUE;
	}
}
// 현재 frame을 보여주는 함수
CVisibleFrame::CVisibleFrame()
{
	m_pMainWnd = NULL;
	Create(WS_EX_TOOLWINDOW, VERSION, WS_POPUP | WS_SYSMENU, CRect(100, 100, 200, 200), GetDesktopWindow(), NULL, IDR_VITUALTYPE);
}

CVisibleFrame::CVisibleFrame(CMainFrame *pMainWnd)
{
	m_pMainWnd = pMainWnd;
	Create(WS_EX_TOOLWINDOW, VERSION, WS_POPUP | WS_SYSMENU, CRect(100, 100, 200, 200), GetDesktopWindow(), NULL, IDR_VITUALTYPE);
}

CVisibleFrame::~CVisibleFrame()
{
	Finalize();
}

BEGIN_MESSAGE_MAP(CVisibleFrame, EasySkinWnd)
	//{{ _MSG_MAP(CVisibleFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	//	ON_MESSAGE(WM_KEYSTROKE, OnHookKeyboard)
	ON_MESSAGE(WM_FUNCKEYDOWN, OnFuncKeyDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisibleFrame message handlers

//----------------------------------------------------------------------------------------------------------//
//		CallBack 함수.. 일단 지금 화면에 떠 있는 윈도우의 포인터를 가지고 온다.보이는 윈도우 모두를 가지고 온다.
//----------------------------------------------------------------------------------------------------------//

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	char					szWindowTitle[100];
	HWND					hDesktop;
	LONG					lWndStyle;
	CWndList				*pList;
	struct WndDataStruct	stWndData;

	pList = (CWndList *)lParam;
	hDesktop = ::GetDesktopWindow();

	if (hWnd != NULL)
	{
		lWndStyle = ::GetWindowLong(hWnd, GWL_STYLE);

		if ((lWndStyle & WS_VISIBLE) == WS_VISIBLE && (lWndStyle & WS_CHILD) != WS_CHILD)
		{
			::GetWindowText(hWnd, szWindowTitle, 100);

			stWndData.hWnd = hWnd;
			stWndData.bIsNoResponse = FALSE;
			stWndData.bIsWindowSizeZero = FALSE;

			//	윈도우의 Minimize or Maximize 체크
			if ((lWndStyle & WS_MINIMIZE) == WS_MINIMIZE)
				stWndData.uStatus = MINIMIZED;
			else if ((lWndStyle & WS_MAXIMIZE) == WS_MAXIMIZE)
				stWndData.uStatus = MAXIMIZED;
			else
				stWndData.uStatus = STANDARD;

			//	enable Disable 체크..
			//if( ( lWndStyle & WS_DISABLED ) == WS_DISABLED )
			//	stWndData.bIsDisabled	= TRUE;

			stWndData.lExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);

			//	그리고 삽입한다.
			pList->AddLast(stWndData);
		}
		return TRUE;
	}
	else
		return FALSE;
}
//----------------------------------------------------------------------------------------------------------//
//		CallBack 함수.. 화면의 모든 윈도우를 저쭈 화면 밖으로 보낸다.그와 동시에 보이는 윈도우를 리스트에 저장한다.
//----------------------------------------------------------------------------------------------------------//
BOOL CALLBACK EnumWindowsProcWithHide(HWND hWnd, LPARAM lParam)
{
	char					szWindowName[100];
	HWND					hTaskWnd;
	HWND					hVirtualWnd;
	HWND					hMainWnd;
	HWND					hProgWnd;
	//	HWND					hOwnerWnd;
	LONG					lWndStyle;
	CWndList				*pList;
	int						nPastDesktop;
	int						nScreenX;
	int						nScreenY;
	struct WndDataStruct	stWndData;
	RECT					stRect;
	//	LONG					lExStyle;


	pWnd = (CVisibleFrame *)lParam;
	hTaskWnd = pWnd->m_hTaskBar;
	hMainWnd = pWnd->m_hMainWnd;
	hVirtualWnd = pWnd->m_hWnd;
	hProgWnd = pWnd->m_hProgMan;
	nScreenX = pWnd->m_nScreenX;
	nScreenY = pWnd->m_nScreenY;

	HWND hwnd = GetDesktopWindow();
	SetWindowPos(hwnd, NULL, 100, 100, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);

	nPastDesktop = pWnd->m_nPastDesktop;
	pList = &(pWnd->m_pWndList[nPastDesktop]);

	if (hWnd != NULL)
	{
		lWndStyle = ::GetWindowLong(hWnd, GWL_STYLE);
		if ((lWndStyle & WS_CHILD) != WS_CHILD)
		{
			if (pWnd->IsSkippedWindow(hWnd) == FALSE)
			{
				if ((lWndStyle & WS_VISIBLE) == WS_VISIBLE) //&& 
				{
					::GetWindowText(hWnd, szWindowName, 100);
					//TRACE("WindowName [%s] Handle[%X] \n", szWindowName , ( UINT )hWnd );
					if (pWnd->m_pNoResponseWndList->FindMatchedHwnd(hWnd, stWndData))
					{
						//TRACE("윈도우가.. 응답이 없는 윈도우 리스트에 포함되어 있다.\n");
						return TRUE;
					}
					//	윈도우의 범위를 읽어서.. 만약 범위 자체가..
					//	윈도우 밖이면.. 무시한다.
					::GetWindowRect(hWnd, &stRect);
					if (((MINRANGEY <= stRect.top) && (stRect.top <= nScreenY)) ||
						((lWndStyle & WS_MINIMIZE) == WS_MINIMIZE))
					{
						// 현재 desktop 화면에 존재하는 경우
						//TRACE("WindowName [%s] Handle[%X] [%d] 화면 안이라서.. 한다.\n.\n", szWindowName , ( UINT )hWnd , stRect.top );
					}
					else
					{
						// 현재 desktop 화면에 존재하지 않고 다른 desktop 화면에 존재하는 경
						//TRACE("WindowName [%s] Handle[%X] [%d]는 화면 밖이라서 무시한다.\n", szWindowName , ( UINT )hWnd , stRect.top );
						return TRUE;
					}
					stWndData.hWnd = hWnd;
					//	윈도우의 Minimize or Maximize 체크
					if ((lWndStyle & WS_MINIMIZE) == WS_MINIMIZE)
						stWndData.uStatus = MINIMIZED;
					else if ((lWndStyle & WS_MAXIMIZE) == WS_MAXIMIZE)
						stWndData.uStatus = MAXIMIZED;
					else
						stWndData.uStatus = STANDARD;

					//	enable Disable 체크..
					//if( ( lWndStyle & WS_DISABLED ) == WS_DISABLED )
					//	stWndData.bIsDisabled	= TRUE;
					stWndData.lExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
					stWndData.bIsNoResponse = FALSE;
					stWndData.bIsWindowSizeZero = FALSE;
					stWndData.Processed = FALSE;
					//	그리고 삽입한다.
					pList->AddLast(stWndData);
					//				pWnd->HideWindow( nPastDesktop , hWnd );
				}
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

int CVisibleFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	HWND hWnd2 = NULL;
	WNDCLASS WndClass;
	HINSTANCE hInstance2 = NULL;

	//후보_final
	if (EasySkinWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*초기 desktop 개수 입력 받기*/


	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance2, MAKEINTRESOURCE(IDI_RABBITICO));
	WndClass.hInstance = hInstance2;
	WndClass.lpfnWndProc = WndProc2;
	WndClass.lpszClassName = lpszClass2;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	hWnd2 = CreateWindow(lpszClass2, lpszClass2, WS_EX_TOPMOST | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 450, 135, NULL, (HMENU)NULL, hInstance2, NULL);
	Initialize();

	::ShowWindow(hWnd2, 4);
	::SetWindowPos(hWnd2, HWND_TOPMOST, (X_screen_size / 2) - 200, (Y_screen_size / 2) - 120, X_screen_size - 350 - 80 - 80, Y_screen_size - 100 + 40, SWP_NOZORDER);
	//SetWindowPos(hwnd, HWND_ORDER, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	return 0;
}


//----------------------------------------------------------------------------------------------------------//
//							Initialize: 각종 변수와 리스트를 초기화 한다.
//----------------------------------------------------------------------------------------------------------//
void CVisibleFrame::Initialize()
{
	TRACE("============= CVisibleFrame initialization ===================\n");
	CString sInfo;
	DEVMODE mode;
	check = 0;
	//	기타 플레그 설정
	m_nCurrentDesktop = 0;
	m_nPastDesktop = 0;
	m_nXLength = 0;
	m_nYLength = 0;
	m_nScreenX = 0;
	m_uSelectedMenuID = 0;
	//m_pITaskObject		= NULL;
	m_bIsWndDeleted = FALSE;
	m_bIsInformDlgOpen = FALSE;
	m_bIsSwitching = FALSE;
	//m_bIsSystemMenuOpened	= FALSE;	//	토순이 메뉴를 삽입할 시스템 메뉴가 떠 있는지 본다.
	m_nDesktopCount = DESKTOPCOUNT;		//	Desktop의 수를 9개로 한다.
	m_hMainWnd = NULL;
	m_dwVisibleWndThreadId = ::GetCurrentThreadId();	//Visible 윈도우의 스레드 아이디를 얻는다.

														//InitTaskbar();
	FindSystemBaseWindow();
	m_popUpMenu.LoadMenu(IDR_POPUPMENU);
	//	스레드에서 만들게 한다.
	//	Desktop의 윈도우를 관리하는 리스트를 만든다.
	CreateWndList();
	//	보이는 모든 윈도우의 포인터를 리스트 0에 넣는다.
	ReadAllVisibleWindowIgnorePos(0);
	//	그리고 Display의 크기를 받는다.
	::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);
	m_nXLength = mode.dmPelsWidth;// Chanyoung jang  
	m_nYLength = mode.dmPelsHeight; // Chanyoung jang 
	m_nScreenX = mode.dmPelsWidth;
	m_nScreenY = mode.dmPelsHeight;
	g_pVisibleWnd = this;

	m_bSetEndThread = FALSE;
	m_bIsEndThread = FALSE;

	//데스크톱 개수 설정

	desktop_index_pre = 0;			//jangcytof
	desktop_index = 0;			//jangcytof

	X_screen_size = m_nScreenX;
	Y_screen_size = m_nScreenY;
	TRACE("\n============= 이중모니터 가로방향 해상도 얼마? = %d ===================\n",	X_screen_size);
	TRACE("============= 이중모니터 세로방향 해상도 얼마? = %d ===================\n",	Y_screen_size);

	if (X_screen_size == 1920 && Y_screen_size == 1080) {
		scaledScreenX = X_screen_size / 8;
		scaledScreenY = Y_screen_size / 5;

		scaledScreenX_set = X_screen_size / 5;
		scaledScreenY_set = Y_screen_size / 8;
		TRACE("\n1\n");
		TRACE("============= CB 가로방향 해상도 얼마? = %d ===================\n", scaledScreenX);
		TRACE("=============== CB 세로방향 해상도 얼마? = %d ===================\n", scaledScreenY);
		TRACE("============= SET 가로방향 해상도 얼마? = %d ===================\n", scaledScreenX_set);
		TRACE("=============== SET 세로방향 해상도 얼마? = %d ===================\n", scaledScreenY_set);
	}

	else if (X_screen_size == 1920 && Y_screen_size == 1200) {
		scaledScreenX = m_nScreenX / 8;
		scaledScreenY = m_nScreenY / 6;

		scaledScreenX_set = m_nScreenX / 5.5;
		scaledScreenY_set = m_nScreenY / 10;
		TRACE("\n2\n");
		TRACE("============= CB 가로방향 해상도 얼마? = %d ===================\n", scaledScreenX);
		TRACE("=============== CB 세로방향 해상도 얼마? = %d ===================\n", scaledScreenY);
		TRACE("============= SET 가로방향 해상도 얼마? = %d ===================\n", scaledScreenX_set);
		TRACE("=============== SET 세로방향 해상도 얼마? = %d ===================\n", scaledScreenY_set);
	}
	
	else {
		TRACE("\n3\n");
		scaledScreenX = m_nScreenX / 8;
		scaledScreenY = m_nScreenY / 5;

		scaledScreenX_set = m_nScreenX / 5;
		scaledScreenY_set = m_nScreenY / 8;
		TRACE("============= CB 가로방향 해상도 얼마? = %d ===================\n", scaledScreenX);
		TRACE("=============== CB 세로방향 해상도 얼마? = %d ===================\n", scaledScreenY);
		TRACE("============= SET 가로방향 해상도 얼마? = %d ===================\n", scaledScreenX_set);
		TRACE("=============== SET 세로방향 해상도 얼마? = %d ===================\n", scaledScreenY_set);
	}

	MakeDesktopMap();			//jangcytof
	MakeCurrentDesktopBlock(0);	//jangcytof
	wait = 0;
	positive = 0;
	negative = 0;
	/////////////////////////////////////////// control box ////////////////////////////////////
	Red = 0;
	TempPos = 0;
	TempPos_pre = 0;
	Current_desktop_X = 0;
	Current_desktop_X_pre = 0;

	hBrush = NULL;

	NumofMonitors = GetSystemMetrics(SM_CMONITORS);
	//TRACE("============= 다중 모니터 개수 = %d ===================\n",NumofMonitors);
	//TRACE("============= 스크린 해상도 = %d ===================\n", m_nScreenX);
	//TRACE("============= 스크린 해상도 = %d ===================\n", m_nScreenY);

}

//----------------------------------------------------------------------------------------------------------//
//							Finalize: 메모리를 날린다.
//----------------------------------------------------------------------------------------------------------//
void CVisibleFrame::Finalize()
{
	delete[] m_pWndList;
	delete[] m_phActivateWnd;
	delete m_pNoResponseWndList;
	delete m_pOwnerWndList;
	delete m_pCmdList;
	DeleteObject(hBrush);

	//	TaskBar를 버린다.
	//ReleaseTaskbar();
	m_bSetEndThread = TRUE;
	//	그리고는 스레드가 끝이 날때 까지 기다린다.
	while (1)
	{
		if (m_bIsEndThread == TRUE)
			break;
		Sleep(1);
	}
}

//----------------------------------------------------------------------------------------------------------//
//	MakeDesktopMap: 전체 desktop 맵을 설정하고 이를 보여 준다.  by jangcytof
//----------------------------------------------------------------------------------------------------------//
void CVisibleFrame::MakeDesktopMap()
{
	////TRACE("여기 까지 들어오나 ?? \n" );
	m_desktopmap2.Create(WS_EX_TOOLWINDOW, "DESKTOP_MAP_by_jangcytof2", WS_OVERLAPPED | WS_VISIBLE | WS_DISABLED, //WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU , 
		CRect(m_nScreenX - 350 - 80 + 80, m_nScreenY - 100, m_nScreenX - 50 - 80 + 80, m_nScreenY - 48), NULL, NULL, NULL); //jangcytof //m_nScreenX - 49

	m_desktopmap3.Create(WS_EX_TOOLWINDOW, "DESKTOP_MAP_by_jangcytof3", WS_OVERLAPPED | WS_VISIBLE | WS_DISABLED, //WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU , 
		CRect(m_nScreenX - 350 - 80 + 80, m_nScreenY - 100, m_nScreenX - 50 - 80 + 80, m_nScreenY - 48), NULL, NULL, NULL); //jangcytof //m_nScreenX - 49

	m_desktopmap4.Create(WS_EX_TOOLWINDOW, "DESKTOP_MAP_by_jangcytof4", WS_OVERLAPPED | WS_VISIBLE | WS_DISABLED, //WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU , 
		CRect(m_nScreenX - 350 - 80 + 80, m_nScreenY - 100, m_nScreenX - 50 - 80 + 80, m_nScreenY - 48), NULL, NULL, NULL); //jangcytof //m_nScreenX - 49
																															//if (numofdesktop == 2)
	m_desktopmap2.LoadBitMap(IDB_FORM_DESKTOPMAP2);
	//else if (numofdesktop == 3)
	m_desktopmap3.LoadBitMap(IDB_FORM_DESKTOPMAP3);
	//else if (numofdesktop == 4)
	m_desktopmap4.LoadBitMap(IDB_FORM_DESKTOPMAP4);
	//우선 세개 다 만들고 show안했다가 마지막에 show하기..? or show해놓고 next누르면 나머지 두개 지우기

	m_desktopmap2.SetTransparent(RGB(255, 255, 255));
	m_desktopmap3.SetTransparent(RGB(255, 255, 255));
	m_desktopmap4.SetTransparent(RGB(255, 255, 255));

	m_desktopmap2.ShowWindow(SW_HIDE);
	m_desktopmap3.ShowWindow(SW_HIDE);
	m_desktopmap4.ShowWindow(SW_HIDE);

	//m_desktopmap2.Show();
	//m_desktopmap3.Show();
	//m_desktopmap4.Show();

}

//----------------------------------------------------------------------------------------------------------//
//	MakeCurrentDesktopBlock: 전체 desktop 맵에서 현재 화면의 위치를 보여준다.  by jangcytof
//----------------------------------------------------------------------------------------------------------//
void CVisibleFrame::MakeCurrentDesktopBlock(int x_direction)
{
	m_desktopblock.Create(WS_EX_TOOLWINDOW, "CURRENT_DESKTOP_BLOCK_by_jangcytof2", WS_POPUPWINDOW, //WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU , 
																								   //CRect(m_nScreenX - 350 + 80, m_nScreenY - 100, m_nScreenX - 350 + 160, m_nScreenY - 100 + 40), NULL, NULL, NULL); //jangcytof
		CRect(m_nScreenX - 350, m_nScreenY - 100, m_nScreenX - 350 + 800, m_nScreenY - 100 + 40), NULL, NULL, NULL); //jangcytof

	m_desktopblock.LoadBitMap(IDB_FORM_DESKTOPBLOCK);

	m_desktopblock.SetTransparent(RGB(255, 255, 255));


	m_desktopblock.Show();
}

//----------------------------------------------------------------------------------------------------------//
//	MakeCurrentDesktopIndex:이동한 좌표를 이용하여 Desktop index 만드는 function.  by jangcytof (XY point에 따라 어떻게 할지를 수정해야함!!!!!!)
//----------------------------------------------------------------------------------------------------------//

int CVisibleFrame::MakeCurrentDesktopIndex(int x_direction)
{
	////TRACE("[뭐지 이건] x_direction: %d   y_direction: %d    m_nScreenX: %d   m_nScreenY: %d   \n", x_direction, y_direction, m_nScreenX, m_nScreenY);
	if (x_direction < 2 * m_nScreenX / 3)
	{
		return 0;
	}
	else if (x_direction < m_nScreenX + 2 * m_nScreenX / 3)
	{
		return 1;
	}
	else if (x_direction < 2 * m_nScreenX + 2 * m_nScreenX / 3)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

//----------------------------------------------------------------------------------------------------------//
//	SetButtons:버튼 비트맵을 설정하고 투명하게 한다. (버튼을 생성하여, 현재 화면의 크기 및 기타를 보여줌)
//----------------------------------------------------------------------------------------------------------//

void CVisibleFrame::SetButtons()
{
	TRACE("");
	m_currentDesktopIndicateWnd.Create(WS_EX_TOOLWINDOW, "현재 데스크탑 표시 윈도우", WS_POPUPWINDOW, CRect((m_nScreenX / 2) - 10, (m_nScreenY / 2) - 10, (m_nScreenX / 2) + 10, (m_nScreenY / 2) + 10), NULL, NULL, NULL); //jangcytof
	m_currentDesktopIndicateWnd.LoadBitMap(IDB_FORM_CURRENTDESKTOPINDICATEWND);
	m_currentDesktopIndicateWnd.SetTransparent(RGB(255, 255, 255)); // jangcytof
	m_currentDesktopIndicateWnd.CenterWindow();
}

//----------------------------------------------------------------------------------------------------------//
//	ReadAllVisibleWindowIgnorePos: 보이는 모든 윈도우를 얻고 나서 제일 처음의 Desktop List View를 삭제하고 제일 끝 부분의 Program Manager를 삭제하여 나머지 윈도우 부분만 선택한다.
//----------------------------------------------------------------------------------------------------------//
void CVisibleFrame::ReadAllVisibleWindowIgnorePos(int nIndex)
{
	::EnumWindows(EnumWindowsProc, (LPARAM)&m_pWndList[nIndex]);
	//	일단 테스크 바는 포인터를 얻어서 놔둔다.
	m_pWndList[nIndex].DeleteOfHwnd(m_hTaskBar);
	//	마지막의 Program Manager를 삭제한다.
	m_pWndList[nIndex].DeleteOfHwnd(m_hProgMan);
	//	그리고 자기 자신의 윈도우를 삭제한다.
	m_pWndList[nIndex].DeleteOfHwnd(m_hWnd);
	m_pWndList[nIndex].DeleteOfHwnd(m_hMainWnd);
}

//----------------------------------------------------------------------------------------------------------//
//	HideAllWindowInID: 일단 보이는 윈도우를 리스트에 넣고..화면에서 다 사라지게 한다. EnumWindowProcWithHide를 호출한다.
//----------------------------------------------------------------------------------------------------------//
void CVisibleFrame::HideAllWindowInID(int nIndex)
{
	CWndNode	*pNode;
	char     szWindowText[100];

	::EnumWindows(EnumWindowsProcWithHide, (LPARAM) this);
	m_pWndList[m_nPastDesktop].ResetIteration();
	while (m_pWndList[m_nPastDesktop].HasMore())
	{
		pNode = m_pWndList[m_nPastDesktop].HasNext();
		//HideWindow( m_nPastDesktop , pNode->m_WndData.hWnd );
		::GetWindowText(pNode->m_WndData.hWnd, szWindowText, 100);
	}
}

//----------------------------------------------------------------------------------------------------------//
//	OnFuncKeyDown: 키보드를 후킹해서 처리하는 함수~ (현재 화면 표시도 있음) by jangcytof
//----------------------------------------------------------------------------------------------------------//

LRESULT CVisibleFrame::OnFuncKeyDown(WPARAM wParam, LPARAM lParam)
{
	return (0);
}

void CVisibleFrame::OnClose()
{
	CWnd::ShowWindow(SW_HIDE);
}

//---------------------------------------------------
//		테스크 바와 바탕화면을 찾는다.
//---------------------------------------------------
void CVisibleFrame::FindSystemBaseWindow()
{
	m_hProgMan = ::FindWindow("Progman", NULL);
	//m_hTaskBar = ::FindWindow( "Shell_TrayWnd" , "");
	m_hTaskBar = ::FindWindow("Shell_TrayWnd", NULL);
	m_hSecondTaskBar = ::FindWindow(_T("Shell_SecondaryTrayWnd"), NULL);
	m_hWorkerW = ::FindWindow(_T("WorkerW"), NULL);

	//if (NULL == m_hSecondTaskBar) TRACE(" ************************************두번째 작업표시줄 못 얻음 \n");
	//else TRACE(" ************************************두번째 작업표시줄 얻음 \n");
	//if (NULL == m_hTaskBar) TRACE(" ************************************첫번째 작업표시줄 못 얻음 \n");
	//else TRACE(" ************************************첫번째 작업표시줄 얻음 \n");
	//if (NULL == m_hProgMan) TRACE(" ************************************이건 뭐야 못 얻음 \n");
	//else TRACE(" ************************************ 이건 뭐야 얻음 \n");

}

void CVisibleFrame::OnDestroy()
{
	EasySkinWnd::OnDestroy();
}


//-------------------------------------------------------------
//		윈도우를 저장할 윈도우 리스트를 메모리 할당한다.
//-------------------------------------------------------------
void CVisibleFrame::CreateWndList()
{
	int i;

	m_phActivateWnd = new HWND[m_nDesktopCount];
	m_pWndList = new CWndList[m_nDesktopCount];
	m_pOwnerWndList = new CWndList;
	m_pNoResponseWndList = new CWndList;
	m_pCmdList = new CCommandList;
	for (i = 0; i < m_nDesktopCount; i++)
	{
		m_phActivateWnd[i] = NULL;
	}
}

BOOL CVisibleFrame::OnEraseBkgnd(CDC* pDC)
{
	EasySkinWnd::OnEraseBkgnd(pDC);
	//	Desktop Index를 새로 그린다
	//	그래야 인덱스가 없어지는걸 막을수 있다.
	//m_desktopIndexWnd.Invalidate( TRUE );
	return TRUE;
}

//---------------------------------------------------------------------
//		윈도우 스타일에서 내가 정의한 윈도우 상태을 넘겨주는 함수 윈도우 리스트에 윈도우 구조체를 저장할때 사용	윈도우 핸들을 넘겨서 찾음..
//---------------------------------------------------------------------
UINT CVisibleFrame::GetWindowStatusFrom(HWND hWnd)
{
	LONG	lStyle;

	lStyle = ::GetWindowLong(hWnd, GWL_STYLE);
	//	윈도우의 Minimize or Maximize 체크
	if ((lStyle & WS_MINIMIZE) == WS_MINIMIZE)
		return MINIMIZED;
	else if ((lStyle & WS_MAXIMIZE) == WS_MAXIMIZE)
		return MAXIMIZED;
	else if ((lStyle & WS_VISIBLE) != WS_VISIBLE)
		return HIDE;
	else
		return STANDARD;
}
//---------------------------------------------------------------------
//		윈도우 스타일에서 내가 정의한 윈도우 상태을 넘겨주는 함수 윈도우 리스트에 윈도우 구조체를 저장할때 사용
//---------------------------------------------------------------------
UINT CVisibleFrame::GetWindowStatusFrom(LONG lStatus)
{
	if (lStatus == SW_MAXIMIZE)
		return MAXIMIZED;
	else if (lStatus == SW_MINIMIZE)
		return MINIMIZED;
	else
		return STANDARD;
}
//---------------------------------------------------------------------
//		내가 정의한 윈도우 상태에서 윈도우 스타일을 넘겨주는 함수ShowWindow를 호출할때 쓴다.
//---------------------------------------------------------------------
LONG CVisibleFrame::GetWindowStyleFrom(UINT uStatus)
{
	switch (uStatus)
	{
	case MINIMIZED:
		return SW_MINIMIZE;
	case MAXIMIZED:
		return SW_MAXIMIZE;
	default:
		return SW_SHOWNA;
	}
}

//--------------------------------------------------------
//		윈도우가 무시해야 하는 윈도우 핸들인지..즉 테스크 바.. 프로그램 메니저...그리고 Vitual Desktop 프로그램..을 체크한다.
//--------------------------------------------------------
BOOL CVisibleFrame::IsSkippedWindow(HWND hWnd)
{
	char szClassName[100];

	//	만약 가상 Desktop의 윈도우 핸들 또는 시스템 쪽이면..
	if ( /*hWnd == m_hWnd		||
		 hWnd == m_hMainWnd ||
		 hWnd == m_hTaskBar	||
		 hWnd == m_hProgMan ||*/
		 //hWnd == m_activateIndicateWnd.m_hWnd || 
		hWnd == m_currentDesktopIndicateWnd.m_hWnd)
		return TRUE;
	//	만약 SysShadow 윈도우 또는 툴팁 윈도우면..
	//	역쉬 넘어간다.
	::GetClassName(hWnd, szClassName, 100);
	if ((lstrcmp(szClassName, "SysShadow") == 0) ||
		(lstrcmp(szClassName, "tooltips_class32") == 0))
		return TRUE;
	return FALSE;
}

//-------------------------------------------------------------
//		중복을 찾는다..혹시나.. 여기 윈도우가.. 다른곳에 당겨올수 있으니까..
//-------------------------------------------------------------
void CVisibleFrame::RemoveDuplication(int nIndex)
{
	CWndNode				*pNode;
	int						i;
	struct WndDataStruct	stWndData;
	struct WndDataStruct	stTempWndData;
	char					szWindowName[100];
	CString					sInfo;
	HWND					hParentWnd;
	LONG					lStyle;
	BOOL					bIsSizeZero;

	bIsSizeZero = FALSE;

	m_pWndList[nIndex].ResetIteration();
	while (m_pWndList[nIndex].HasMore())
	{
		pNode = m_pWndList[nIndex].HasNext();
		stWndData = pNode->m_WndData;
		//bIsSizeZero = IsRestoreSizeZero( stWndData.hWnd );

		if (stWndData.bHasTaskButton)
		{
			//TRACE("[INF] 테스크바 버튼을 가지고 있다. WindowName [%s] [%X] \n", szWindowName , (UINT) stWndData.hWnd );
			m_pWndList[nIndex].SetHasToolbarButton(stWndData.hWnd, TRUE);
		}
		else
		{
			//TRACE("[INF] 테스크바 버튼이 없다. WindowName [%s] [%X] \n", szWindowName , (UINT) stWndData.hWnd );
			m_pWndList[nIndex].SetHasToolbarButton(stWndData.hWnd, FALSE);
		}

		for (i = nIndex + 1; i < m_nDesktopCount; i++)
		{
			//	만약 윈도우가.. 죽어 있다면..그것은 그대로 놔둘 필요가 있다..그렇지 않으면.. 나중에.. 다시.. Active 되더라도..보이지가 않는다..
			::GetWindowText(stWndData.hWnd, szWindowName, 100);
			if (stWndData.bIsNoResponse == TRUE)
			{
				//TRACE("[우우웅..] 현재[%s] 것은 응답없는 윈도우다.다른 윈도우[%d]에 있어서 [%d]에서 지운다. \n" , szWindowName , i , nIndex );
				continue;
			}
			//	만약 최소화 상태이고..다른곳에도 있으면.. 현재 위치에 있는것을 지운다.20021029 윈도우 사이즈중.. 어느 하나라도 0 인것은 Restore 가 되게 했다. 그러므로 그런 윈도우 역시.. Minimized 와 같이 취급되어야 한다.
			if ((stWndData.uStatus == MINIMIZED) || (bIsSizeZero == TRUE))
			{
				if (m_pWndList[i].FindMatchedHwnd(stWndData.hWnd, stTempWndData))
				{
					m_pWndList[nIndex].DeleteOfHwnd(stWndData.hWnd);
					if (stTempWndData.uStatus != MINIMIZED)
					{
						lStyle = ::GetWindowLong(stWndData.hWnd, GWL_STYLE);
						lStyle = lStyle & ~WS_MINIMIZE;
						::SetWindowLong(stWndData.hWnd, GWL_STYLE, lStyle);
					}
				}
			}
			//	찾아서 지우는거 보다..리스트기 때문에..그냥.. 지우는 함수를 호출하는것이..더 효율적이다..
			else if (m_pWndList[i].DeleteOfHwnd(stWndData.hWnd))
			{
				if (m_phActivateWnd[i] == stWndData.hWnd)
					m_phActivateWnd[i] = NULL;
				hParentWnd = ::GetParent(stWndData.hWnd);
				if (IsSkippedWindow(hParentWnd))
				{
					continue;
				}
				::GetWindowText(stWndData.hWnd, szWindowName, 100);
				//	TRACE("[%d]에 있는 윈도우 [%s][%X]가 중복되어 [%d]에도 있습니다.\n [%d]에 있는 윈도우를 현재 데스크 탑[%d]로 이동합니다.\n",
				//		nIndex, szWindowName, (UINT)stWndData.hWnd, i, i, nIndex);
				sInfo.Format("[%d]에 있는 윈도우 [%s][%X]가 중복되어 [%d]에도 있습니다.\n [%d]에 있는 윈도우를 현재 데스크 탑[%d]로 이동합니다.\n",
					nIndex, szWindowName, (UINT)stWndData.hWnd, i, i, nIndex);
			}
		}
	}
}

////////////////////////////////////  DESKTOP의 이동시 화면을 숨기는 함수 //////////////////////////////
void CVisibleFrame::HideWindow(int nIndex, HWND hWnd)
{
	char	szWindowName[100];
	LONG	lStyle;
	CRect	stRect;
	struct	WndDataStruct stWndData;
	HWND	hOwnerWnd;
	BOOL	bIsSizeZero;

	::GetWindowText(hWnd, szWindowName, 100);
	bIsSizeZero = FALSE;

	// DESKTOP_MAP_by_jangcytof 은 항상 띄워 두기 위해 절때 HIDE하지 않는다.  jangcytof
	if (strcmp(szWindowName, "DESKTOP_MAP_by_jangcytof")*strcmp(szWindowName, "CURRENT_DESKTOP_BLOCK_by_jangcytof")*strcmp(szWindowName, "CONTROL BOX") != 0)
	{
		if (IsWindowAlive(hWnd))
		{
			lStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
			::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE | SWP_HIDEWINDOW);
			hOwnerWnd = ::GetWindow(hWnd, GW_OWNER);
			//	소유된 윈도우 중에서 EX_APPWINDOW가 설정되어 캡션을 갖는 윈도우가 발견되어 수정했다.
			::GetWindowRect(hWnd, &stRect);
			//	테스크바를 가지는 윈도우 중에 간혹 보이는 화면 가운데 윈도우를 띄워놓고..그 크기를 0 으로 해놓아서 보이지 않게 해놓은 윈도우가 있다
			//	그런경우는 여기에 포함시키지 않는다. 그냥 숨기도록 하자.
			if (((hOwnerWnd == NULL) || ((lStyle & WS_EX_APPWINDOW) == WS_EX_APPWINDOW)))
			{
				lStyle = lStyle | WS_EX_TOOLWINDOW;
				lStyle = lStyle & ~WS_EX_APPWINDOW;
				::SetWindowLong(hWnd, GWL_EXSTYLE, lStyle);
			}
			lStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);

			////	스크린 안에 있으면 옮긴다.그렇지 않으면 그냥.. NoMove 한다.
			//if( ( MINRANGEY <= stRect.top ) && ( stRect.top <= m_nScreenY ) )  
			//{
			//	//	SetWindowLong 이 먹지 않는 윈도우가 간혹 있다 그런경우는 그냥 숨기고 보이지는 않는다.
			//	if( ( lStyle & WS_EX_APPWINDOW ) == WS_EX_APPWINDOW )
			//	{
			//		::SetWindowPos( hWnd , NULL , stRect.left + m_nXLength , stRect.top + m_nYLength , 0 , 0 , SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER );
			//		//TRACE("[INF] 윈도우 [%s][%X]에 AppWindow 설정이 되어 있어서 옮기면서 보이지 않는다.. . \n" , szWindowName , (UINT)hWnd );
			//	}
			//	else
			//	{
			//		::SetWindowPos( hWnd , NULL , stRect.left + m_nXLength , stRect.top + m_nYLength , 0 , 0 , SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW );
			//		//TRACE("[INF] 윈도우 [%s][%X]에 AppWindow 설정이 없어서 옮기면서 보인다. 화면 안에 있네??\n" , szWindowName , (UINT)hWnd );
			//	}
			//	//TRACE("[INF] 윈도우 [%s][%X]를 숨긴다 . \n" , szWindowName , (UINT)hWnd );
			//}
			//else
			//{
			if ((lStyle & WS_EX_APPWINDOW) == WS_EX_APPWINDOW)
			{
				::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
				//TRACE("[INF] 윈도우 [%s][%X]에 AppWindow 설정이 되어 있어서 옮기면서 보이지 않는다.. . \n" , szWindowName , (UINT)hWnd );
			}
			else
			{
				::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
				//TRACE("[INF] 윈도우 [%s][%X]에 AppWindow 설정이 없어서 옮기면서 보인다. 화면 밖에 있네??\n" , szWindowName , (UINT)hWnd );
			}
			//TRACE("[INF] 윈도우 [%s][%X]를 숨긴다 . \n" , szWindowName , (UINT)hWnd );

			//}
		}
		//	살아있지 않으면..
		else
		{
			stWndData.hWnd = hWnd;
			m_pNoResponseWndList->AddLast(stWndData);
			m_pWndList[nIndex].SetIsNoResponse(hWnd, TRUE);
		}
	}
}

////////////////////////  윈도우 창을 화면에 보여줄지 말지를 결정하는 function ///////////////////
void CVisibleFrame::ShowWindow(int nIndex, HWND hWnd, LONG lStyle, BOOL bIsActivate)
{
	char					szWindowName[100];
	LONG					lFlag;
	RECT					stRect;
	int						nAddX;
	int						nAddY;
	struct WndDataStruct	stWndData;
	HWND					hOwnerWnd;
	LONG					lCurrentStyle;

	lFlag = SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED;
	nAddX = m_nXLength;
	nAddY = m_nYLength;

	::GetWindowText(hWnd, szWindowName, 100);
	//	To Do : 포커스 문제는 여기 보기.
	if (bIsActivate == FALSE)
		lFlag = lFlag | SWP_NOACTIVATE;
	else
		;//TRACE("[INF] 윈도우 [%s][%X]가 Active윈도우다. \n" , szWindowName , (UINT)hWnd );

		 //	살아있으면 날린다.
	if (IsWindowAlive(hWnd))
	{
		if (m_pWndList[nIndex].IsNoResponse(hWnd))
		{
			m_pWndList[nIndex].SetIsNoResponse(hWnd, FALSE);
			m_pNoResponseWndList->DeleteOfHwnd(hWnd);
		}

		//	만약 윈도우 속성이 숨겨져 있는 사이에 속성이 UnVisible로 바뀌었다면..콘솔 클레스인 경우에는..SetWindowLong이 먹지 않아서 그냥 숨겨 두었다.따라서 콘솔 윈도우는 숨겨졌는거지... 지우기 위한 것이 
		//	아니므로 이렇게 두었다.
		lCurrentStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
		if ((::IsWindowVisible(hWnd) == FALSE) &&
			((lCurrentStyle & WS_EX_APPWINDOW) != WS_EX_APPWINDOW))
		{
			m_pWndList[nIndex].FindMatchedHwnd(hWnd, stWndData);
			lStyle = stWndData.lExStyle;
			::SetWindowLong(hWnd, GWL_EXSTYLE, lStyle);
			m_pWndList[nIndex].DeleteOfHwnd(hWnd);
			::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
			//TRACE("[INF] 윈도우 [%s][%X]가 숨겨져 있는동안 UnVisible로 설정되었다. \n" , szWindowName , (UINT)hWnd );
		}

		else
		{
			::GetWindowRect(hWnd, &stRect);

			//	스크린 안에 있으면 FrameChange를 한번 날린다.왜냐하면 같이 상관관계가 있게 움직이는 윈도우가 서로 간섭을 받아 움직인 것일수도 있기 때문이다.
			if ((MINRANGEY <= stRect.top) && (stRect.top <= m_nScreenY))
			{
				if (m_pWndList[nIndex].FindMatchedHwnd(hWnd, stWndData))
				{
					::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_HIDEWINDOW);
					::SetWindowLong(hWnd, GWL_EXSTYLE, stWndData.lExStyle);
					::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
				}
				return;
			}
			if (m_pWndList[nIndex].FindMatchedHwnd(hWnd, stWndData))
			{
				::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_HIDEWINDOW | SWP_NOZORDER | SWP_NOACTIVATE);
				lStyle = stWndData.lExStyle;
				::SetWindowLong(hWnd, GWL_EXSTYLE, lStyle);
				hOwnerWnd = ::GetWindow(hWnd, GW_OWNER);
				::SetWindowPos(hWnd, NULL, stRect.left - nAddX, stRect.top - nAddY, 0, 0, lFlag);
				//TRACE("[INF] 윈도우 [%s][%X]를 보인다. \n" , szWindowName , (UINT)hWnd );
			}
			else
			{
				//TRACE("어어어엉어~~!! 에러다.. 이건 말도 안된다.\n");
			}
		}
	}
	else
	{

	}
}

BOOL CVisibleFrame::IsWindowAlive(HWND hWnd)
{
	DWORD dValue;
	DWORD dTick;

	dTick = GetTickCount();
	//	메시지를 보내어 처리 되는가 본다.. ㅡㅡ;;
	if (::SendMessageTimeout(hWnd, WM_NULL,
		NULL, NULL, SMTO_NORMAL, WAITRESPONSETIME, &dValue) == 0)
	{
		dTick = GetTickCount() - dTick;
		//TRACE("[TICK] IsWindowAlive [%d]ms\n" , dTick );
		return FALSE;
	}
	else
	{
		dTick = GetTickCount() - dTick;
		//TRACE("[TICK] IsWindowAlive [%d]ms\n" , dTick );
		return TRUE;
	}
}

void CVisibleFrame::StartThread()
{
	m_hThread = (HANDLE)_beginthread(ThreadFunc, 0, (void *)this);
}


void CVisibleFrame::MoveDesktopTo(int desktop_X, int desktop_X_pre)
{

	HWND	hToActivateWnd;
	//char	szWindowName[100];
	struct ChangeFocusWndDataStruct stCfwd;
	struct WndDataStruct stTempWndData;
	m_bIsSwitching = TRUE;

	desktop_index_pre = desktop_index;					//jangcytof
	desktop_index = MakeCurrentDesktopIndex(desktop_X);	//jangcytof

	hToActivateWnd = m_phActivateWnd[desktop_index];
	//	그리고.. 데스크 탑 인덱스를 재 설정한다.
	m_nPastDesktop = desktop_index_pre;
	m_nCurrentDesktop = desktop_index;


	struct WndDataStruct	stWndData;
	CWndNode				*currentNode;
	HWND					hActivateWindow;
	HWND					hWnd;

	/******************************************/
	CWnd *cWnd_window;
	cWnd_window = GetDesktopWindow();
	HWND					hDesktop;
	hDesktop = cWnd_window->m_hWnd;

	/******************************************/
	char					szClassName[100];
	char					szWindowName[100];
	RECT					stRect;			//jangcytof
	int						minimap_move_X = desktop_X - desktop_X_pre;
	int						move_X = desktop_X - desktop_X_pre;
	HDC						hdc_tmp;
	int						step_size;
	step_size = m_nScreenX / 80;
	int size = 0;


	int temp1 = 0, temp2 = 0;

	//HWND h_wnd = ::FindWindow(NULL, "파일 탐색기");

	vector<HWND> processedHwnd;


	for (int i = 0; i <= (numofdesktop - 1); i++)
	{
		//TRACE("num of desktop  = %d\n", numofdesktop);
		HideAllWindowInID(i);
		RemoveDuplication(i);

		hActivateWindow = m_phActivateWnd[i];
		m_pWndList[i].ResetIteration();

		while (m_pWndList[i].HasMore())
		{
			currentNode = m_pWndList[i].HasNext();
			stWndData = currentNode->m_WndData;
			hWnd = stWndData.hWnd;

			::GetWindowText(currentNode->m_WndData.hWnd, szWindowName, 100);
			::GetWindowRect(currentNode->m_WndData.hWnd, &stRect);

			::GetClassName(hWnd, szClassName, 100);

			helper.findHWnd();

			// 현재 desktop_index에 맞게 최대화를 그 화면에 가서 하는 function
			if ((GetWindowStatusFrom(hWnd) == MAXIMIZED) == 1) {
				if (std::find(processedHwnd.begin(), processedHwnd.end(), hWnd) != processedHwnd.end())
					continue;
				processedHwnd.push_back(stWndData.hWnd);
				stRect.left = stRect.left - move_X;
				stRect.right = stRect.right - move_X;
				WINDOWPLACEMENT test;
				::GetWindowPlacement(hWnd, &test);
				test.showCmd = 1;
				test.rcNormalPosition.left = stRect.left;
				test.rcNormalPosition.top = 0;
				test.rcNormalPosition.bottom = m_nScreenY;
				test.rcNormalPosition.right = stRect.left + m_nScreenX;
				::SetWindowPlacement(hWnd, &test);

				::SetWindowPos(hWnd, NULL, stRect.left, stRect.top, stRect.right - stRect.left, stRect.bottom - stRect.top, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
				//::MoveWindow(hWnd, m_nScreenX*desktop_index - desktop_X_pre + 10, stRect.top, stRect.right - stRect.left - 20, stRect.bottom - stRect.top, TRUE);
				//TRACE("position = %d\n", m_nScreenX*desktop_index - desktop_X_pre + move_X);
				//::MoveWindow(hWnd, m_nScreenX*desktop_index - desktop_X_pre + move_X, stRect.top, stRect.right - stRect.left, stRect.bottom - stRect.top, TRUE);
			}

			if (desktop_X != desktop_X_pre)
			{
				if (hWnd != m_hSecondTaskBar) {
					//hWnd != m_hProgMan
					if (hWnd != m_hProgMan)
					{
						if (hWnd != helper.getHWnd()) // 바탕화면 아이콘 뒤에 생성된 see-through 창을 고정하는 것임
						{
							if (hWnd != m_hTaskBar)
							{
								if (strcmp(szWindowName, "CONTROL BOX") != 0 && strcmp(szWindowName, "Initial setting") != 0)
								{
									if (hWnd != ::FindWindow("TrayNotifyWnd", NULL))  // Tray창에서 notification 이동 안되게
									{
										if (strcmp(szWindowName, "DESKTOP_MAP_by_jangcytof2") == 0 || strcmp(szWindowName, "DESKTOP_MAP_by_jangcytof3") == 0 || strcmp(szWindowName, "DESKTOP_MAP_by_jangcytof4") == 0) {
											if (std::find(processedHwnd.begin(), processedHwnd.end(), hWnd) != processedHwnd.end())
												continue;
											processedHwnd.push_back(stWndData.hWnd);

											temp1++;
											//	TRACE("i = %d, handle = %d\n", i, stWndData.hWnd);
											if (temp1 != 1)
												printf("break");

											minimap_move_X = minimap_move_X / 24;

											TRACE("						*********** MINIMAP 정보 ***********					\n");
											TRACE("[minimap_move_X] = %d \n", minimap_move_X);
											TRACE("[minimap 변경 전 위치] = %d \n", stRect.left);
											stRect.left = stRect.left - minimap_move_X;
											TRACE("[minimap 변경 후 위치] = %d \n", stRect.left);

											stRect.right = stRect.right - minimap_move_X;
											::MoveWindow(hWnd, stRect.left, stRect.top, stRect.right - stRect.left, stRect.bottom - stRect.top, TRUE);
										}

										//if (strcmp(szWindowName, "바탕 화면") == 0 && stWndData.Processed == FALSE) {}

										else if (m_pWndList[i].FindMatchedHwnd(hWnd, stWndData))
										{
											if (std::find(processedHwnd.begin(), processedHwnd.end(), hWnd) != processedHwnd.end())
												continue;
											processedHwnd.push_back(stWndData.hWnd);

											if (!((stRect.top > m_nScreenY * 20 / 35) && (stRect.bottom < m_nScreenY * 31 / 32))) // task bar 미리보기 이동 방지 위해, 차후에 hwnd을 이용하여 수정해야함
											{
												stRect.left = stRect.left - move_X;
												stRect.right = stRect.right - move_X;
												//TRACE("[window 변경 후 위치] = %d \n", stRect.left);

												::SetWindowPos(hWnd, NULL, stRect.left, stRect.top, stRect.right - stRect.left, stRect.bottom - stRect.top, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//	그리고 현재 윈도우 표시기를 보여준다.		jangcytof
	if (desktop_index_pre != desktop_index)		//jangcytof
	{
		m_currentDesktopIndicateWnd.SetCurrentDesktopIndex(desktop_index + 1);		//jangcytof
		m_currentDesktopIndicateWnd.Show();
	}
	m_bIsSwitching = FALSE;
	//Sleep(1);
	//TRACE("* wait 0으로 바뀌기 바로 전[wait] = %d\n", wait);
	wait = 0;
	//TRACE("* wait 0으로 바뀌고 바로 후[wait] = %d\n", wait);
}

void CVisibleFrame::DesktopPosInit()
{
	HWND	hToActivateWnd;
	struct ChangeFocusWndDataStruct stCfwd;
	struct WndDataStruct stTempWndData;
	m_bIsSwitching = TRUE;

	struct WndDataStruct	stWndData;
	CWndNode				*currentNode;
	HWND					hActivateWindow;
	HWND					hWnd;

	char					szClassName[100];
	char					szWindowName[100];
	RECT					stRect;			//jangcytof

	HDC						hdc_tmp;
	int						step_size;
	step_size = m_nScreenX / 80;
	int size = 0;

	int temp1 = 0, temp2 = 0;

	vector<HWND> processedHwnd;

	helper.findHWnd();

	for (int i = 0; i <= (numofdesktop - 1); i++)
	{
		//HideAllWindowInID(i);
		//RemoveDuplication(i);

		hActivateWindow = m_phActivateWnd[i];
		m_pWndList[i].ResetIteration();

		while (m_pWndList[i].HasMore())
		{
			currentNode = m_pWndList[i].HasNext();
			stWndData = currentNode->m_WndData;
			hWnd = stWndData.hWnd;

			::GetWindowText(currentNode->m_WndData.hWnd, szWindowName, 100);
			::GetWindowRect(currentNode->m_WndData.hWnd, &stRect);
			::GetClassName(hWnd, szClassName, 100);

			if (hWnd != helper.getHWnd()) // 바탕화면 아이콘 뒤에 생성된 see-through 창을 고정하는 것임
			{
				if (hWnd != m_hSecondTaskBar) {
					if (hWnd != m_hProgMan)	// 바탕화면 아이콘이 화면과 함께 움직이도록 하는것임
					{
						if (hWnd != m_hTaskBar)
						{
							if (strcmp(szWindowName, "CONTROL BOX") != 0 && strcmp(szWindowName, "CONTROL BOX") != 0)
							{
								if (hWnd != ::FindWindow("TrayNotifyWnd", NULL))  // Tray창에서 notification 이동 안되게
								{

									if (m_pWndList[i].FindMatchedHwnd(hWnd, stWndData))
									{
										if (std::find(processedHwnd.begin(), processedHwnd.end(), hWnd) != processedHwnd.end())
											continue;
										processedHwnd.push_back(stWndData.hWnd);

										if (!((stRect.top > m_nScreenY * 20 / 35) && (stRect.bottom < m_nScreenY * 31 / 32))) // task bar 미리보기 이동 방지 위해, 차후에 hwnd을 이용하여 수정해야함
										{
											stRect.left = 0;
											stRect.right = m_nScreenX;
											::SetWindowPos(hWnd, NULL, stRect.left, stRect.top, stRect.right - stRect.left, stRect.bottom - stRect.top, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);

										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void CVisibleFrame::ShowVisibleFrame()
{
	RECT stRect;

	::GetWindowRect(m_hWnd, &stRect);
	if (stRect.top - m_nYLength >= MINRANGEY &&
		stRect.top - m_nYLength <= m_nScreenY)
		::SetWindowPos(m_hWnd, NULL, stRect.left - m_nXLength, stRect.top - m_nYLength, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
	else
		::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
}