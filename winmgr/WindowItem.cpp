#include "StdAfx.h"
#include "WindowItem.h"
#include <Psapi.h>
#include <shellapi.h>

namespace winmgr {
  using namespace System::Text::RegularExpressions;

  WindowItem::WindowItem(HWND hwnd) {
    wchar_t data[256];
    this->hwnd = hwnd;

    GetWindowText(hwnd, data, 255);
    this->title = gcnew String(data);

    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    this->pid = gcnew Int32(pid);
    HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
    GetProcessImageFileName(proc, data, 255);
    this->executable = gcnew String(data);
	SHFILEINFO sfi = {0};
	SHGetFileInfo(data, -1, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON);
  }

  bool WindowItem::matches(WMQuery ^query) {
    return query->is_match(this->title);
  }

  void WindowItem::activate(void) {
    DWORD mythread, curthread, newthread;
    HWND curwindow;
    curwindow = GetForegroundWindow();
    if (!curwindow) {
      curwindow = FindWindowA("Shell_TrayWnd", NULL);
    }

    if (IsIconic(this->hwnd)) {
      ShowWindow(this->hwnd, SW_RESTORE);
    }

    curthread = GetWindowThreadProcessId(curwindow, NULL);
    mythread = GetCurrentThreadId();
    newthread = GetWindowThreadProcessId(this->hwnd, NULL);

    AttachThreadInput(mythread, newthread, TRUE);
    AttachThreadInput(mythread, curthread, TRUE);
    AttachThreadInput(curthread, newthread, TRUE);

    SetForegroundWindow(this->hwnd);

    AttachThreadInput(mythread, newthread, FALSE);
    AttachThreadInput(mythread, curthread, FALSE);
    AttachThreadInput(curthread, newthread, FALSE);
  }
}
