#include "stdafx.h"
#include "HotKeyManager.h"
#include <windows.h>

namespace winmgr {
  using namespace System::Collections::Generic;
  HotKeyManager::HotKeyManager() {
    this->counter = 0;
  }

  bool HotKeyManager::register_hotkey(int mod, int keycode) {
    BOOL ret;
    ret = RegisterHotKey(NULL, this->counter, mod, keycode);
    this->counter++;
    return (ret != 0); /* RegisterHotKey returns nonzero for success */
  }

  void HotKeyManager::BackgroundThread(Object ^sender, DoWorkEventArgs ^ev) {
    tagMSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
      if (msg.message == WM_HOTKEY) {
        /* lookup callback and invoke it. */
      }
    }
  }
}
