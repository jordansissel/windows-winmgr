#pragma once

#include <windows.h>
#include "WMQuery.h"
#include "ImageCache.h"

using namespace System;
using namespace System::Drawing;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;
using namespace System::Windows::Media;

namespace winmgr {
  public ref class WindowItem {
    public:
      property String^ title;
      property String^ winclass;
      property String^ executable;
      property ImageSource^ icon;
      property bool visible;
      property Int32^ pid;
      HWND hwnd;

      WindowItem(HWND hwnd, ImageCache ^iconcache);
      bool matches(WMQuery ^query);
      void activate();
  };
}
