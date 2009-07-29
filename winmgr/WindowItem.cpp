#include "StdAfx.h"
#include "WindowItem.h"
#include <Psapi.h>
#include <shellapi.h>
#include "ImageCache.h"

namespace winmgr {
  /* Undef this so Icon::ExtractAssociatedIcon works properly */
  #undef ExtractAssociatedIcon

  using namespace System::Text::RegularExpressions;
  using namespace System::Windows::Media::Imaging;
  using namespace System::Windows::Interop;
  using namespace System::Collections::Generic;
  using namespace System::IO;

  WindowItem::WindowItem(HWND hwnd, ImageCache ^iconcache) {
    wchar_t data[256];
    DWORD pid;
    DWORD len = 255;

    this->hwnd = hwnd;
    GetWindowText(hwnd, data, len);
    this->title = gcnew String(data);
    this->visible = IsWindowVisible(hwnd);
    GetWindowThreadProcessId(hwnd, &pid);
    this->pid = gcnew Int32(pid);

    /* Skip windows that aren't visible */
    if (this->visible) {
      HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
      QueryFullProcessImageName(proc, 0, data, &len);
      CloseHandle(proc);
      this->executable = gcnew String(data);
      this->icon = iconcache->GetIconForExecutable(this->executable);
	} /* if visible */
  }

  bool WindowItem::matches(WMQuery ^query) {
    return this->visible && query->is_match(this->title);
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
