// winmgr.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winmgr.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                // current instance
TCHAR szTitle[MAX_LOADSTRING];          // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];      // the main window class name

BOOL CALLBACK winproc(HWND window, LPARAM lParam);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // Initialize global strings
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_WINMGR, szWindowClass, MAX_LOADSTRING);

  EnumWindows((WNDENUMPROC) winproc, 0);
  return 0;
}

BOOL CALLBACK winproc(HWND hwnd, LPARAM lParam) {
  LPWSTR title;
  int len = 1024;

  title = (LPWSTR)GlobalAlloc(0, len);
  GetWindowText(hwnd, title, len);
  OutputDebugString(title);
  OutputDebugStringA("\n");
  return TRUE;
}
