#include "stdafx.h"

#pragma once

namespace winmgr {
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections::Generic;

//  delegate void HotKeyDelegate(
  public ref class HotKeyManager {
  public:
    int counter; /* increasing counter for hotkey ids */
    //Dictionary<int, delegate
    HotKeyManager();
    bool register_hotkey(int mod, int keycode);

    void BackgroundThread(Object ^sender, DoWorkEventArgs ^ev);
  };
}
