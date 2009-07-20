#pragma once

#include <windows.h>
#include "WMQuery.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;

namespace winmgr {
  public ref class WindowItem {
    public:
      property String^ title;
      property String^ winclass;
      HWND hwnd;

      WindowItem(HWND hwnd);
      bool matches(WMQuery ^query);
      void activate();
  };
}
