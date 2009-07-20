#include "StdAfx.h"
#include "WindowItem.h"

namespace winmgr {
  using namespace System::Text::RegularExpressions;

  WindowItem::WindowItem(HWND hwnd) {
    wchar_t data[200];
    this->hwnd = hwnd;
    GetWindowText(hwnd, data, 200);
    this->title = gcnew String(data);
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
