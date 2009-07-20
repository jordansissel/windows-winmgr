#include "StdAfx.h"
#include "WindowItem.h"

namespace winmgr {
  WindowItem::WindowItem(HWND hwnd) {
    wchar_t data[200];
    this->hwnd = hwnd;
    GetWindowText(hwnd, data, 200);
    this->title = gcnew String(data);
  }

  bool WindowItem::matches(array<String ^> ^patterns) {
    int i = 0;
    bool match = true;
    for (i = 0; i < patterns->Length; i++) {
      match = match && this->matches(patterns[i]);

      if (!match) {
        break;
      }
    }

    return match;
  }

  bool WindowItem::matches(String ^pattern) {
    if (this->title->Contains(pattern)) {
      return true;
    }
    return false;
  }
}
