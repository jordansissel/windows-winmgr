#include "StdAfx.h"
#include "WindowLister.h"
#include "WindowItem.h"
#include "ImageCache.h"

namespace winmgr { 
  using namespace System;
  using namespace System::Runtime::InteropServices;

  WindowLister::WindowLister(void) {
    this->windows = gcnew ArrayList();
    this->imagecache = gcnew ImageCache();
  }

  ArrayList ^WindowLister::GetWindows() {
    /* This function makes a managed function usable as an unmanaged callback */
    EnumWindowsCallback ^ewc = \
      gcnew EnumWindowsCallback(this, &WindowLister::window_handler);
    pin_ptr<EnumWindowsCallback ^> pinner = &ewc;
    IntPtr ewc_ptr = Marshal::GetFunctionPointerForDelegate(ewc);
    WNDENUMPROC enumproc = static_cast<WNDENUMPROC>(ewc_ptr.ToPointer());
    EnumWindows(enumproc, 0);

    return this->windows;
  }

  /* winapi types because this is invoked by a winapi (EnumWIndows) call */
  BOOL WindowLister::window_handler(HWND hwnd, LPARAM lparam) {
    WindowItem ^wi = gcnew WindowItem(hwnd, this->imagecache);
    if (wi->title->Length > 0 && wi->visible) {
      this->windows->Add(wi);
    }
    return TRUE;
  }
}
