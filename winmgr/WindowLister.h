#include <windows.h>
#include "ImageCache.h"

namespace winmgr {
  delegate BOOL EnumWindowsCallback(HWND hwnd, LPARAM lparam);
  using namespace System::Collections;

  ref class WindowLister {
    public:
      ArrayList ^windows;
      ImageCache ^imagecache;

      WindowLister();
      BOOL window_handler(HWND hwnd, LPARAM lparam);
      ArrayList ^GetWindows();
  };

  ref class WindowHandle {
    HWND hwnd;
  };

}

