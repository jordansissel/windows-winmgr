#pragma once
#include "stdafx.h"

namespace winmgr {
  using namespace System;
  using namespace System::Collections::Generic;
  using namespace System::Windows::Media;

  public ref class ImageCache {
  public:
    ImageCache();

    ImageSource ^GetIconForExecutable(String ^path);
  private:
    Dictionary<String ^, ImageSource ^> ^cache;
  };
}
