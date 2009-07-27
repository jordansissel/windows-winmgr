#include "StdAfx.h"
#include "WindowItem.h"
#include <Psapi.h>
#include <shellapi.h>

namespace winmgr {
  using namespace System::Text::RegularExpressions;
  using namespace System::Windows::Media::Imaging;
  using namespace System::Windows::Interop;
  using namespace System::IO;

  WindowItem::WindowItem(HWND hwnd) {
    wchar_t data[256];
    this->hwnd = hwnd;

    GetWindowText(hwnd, data, 255);
    this->title = gcnew String(data);

    this->visible = IsWindowVisible(hwnd);

    DWORD pid;
    DWORD len = 255;
    GetWindowThreadProcessId(hwnd, &pid);
    this->pid = gcnew Int32(pid);
    HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
    //GetProcessImageFileName(proc, data, 255);
    QueryFullProcessImageName(proc, 0, data, &len);
    this->executable = gcnew String(data);
#undef ExtractAssociatedIcon
    try {
      System::Drawing::Icon ^icon = System::Drawing::Icon::ExtractAssociatedIcon(this->executable);
      MemoryStream ^iconstream = gcnew MemoryStream();
      icon->Save(iconstream);
      IconBitmapDecoder ^ibd = gcnew IconBitmapDecoder(iconstream, BitmapCreateOptions::None, BitmapCacheOption::Default);
      this->icon = ibd->Frames[0];
    } catch (ArgumentException ^) {
      // nothing
    } catch (FileNotFoundException ^) {

    }
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
