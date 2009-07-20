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
}
