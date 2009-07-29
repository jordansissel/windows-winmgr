#include "stdafx.h"
#include "ImageCache.h"
#include <windows.h>
#include <shellapi.h>
#include <vcclr.h>

namespace winmgr {
  #undef ExtractAssociatedIcon
  using namespace System::Drawing;
  using namespace System::IO;
  using namespace System::Windows::Media::Imaging;
  using namespace System;

  ImageCache::ImageCache() {
    this->cache = gcnew Dictionary<String ^, ImageSource ^>();
  }

  /* TODO(sissel): Enumerate resources on the executable and see
   * if there is a higher quality icon available */
  ImageSource ^ImageCache::GetIconForExecutable(String ^path) {
    if (this->cache->ContainsKey(path)) {
      return this->cache[path];
    }

    try {
      Icon ^icon = Icon::ExtractAssociatedIcon(path);
      MemoryStream ^iconstream = gcnew MemoryStream();
      icon->Save(iconstream);
      IconBitmapDecoder ^ibd = \
        gcnew IconBitmapDecoder(iconstream, BitmapCreateOptions::None,
                                BitmapCacheOption::OnLoad);
      this->cache[path] = ibd->Frames[0];
      return ibd->Frames[0];
    } catch (ArgumentException ^) {
      /* nothing */
    } catch (FileNotFoundException ^) {
      /* nothing */
    }

    return nullptr;
  }
}



#if 0
  ImageSource ^ImageCache::GetIconForExecutable(String ^path) {
    if (this->cache->ContainsKey(path)) {
      return this->cache[path];
    }

    SHFILEINFO sfi;
    DWORD ret;
    pin_ptr<const wchar_t> pwcpath = PtrToStringChars(path);
    ret = SHGetFileInfo(pwcpath, -1, &sfi, sizeof(sfi),
                        SHGFI_ICON);

	//return gcnew System::Windows::Media::ImageSource();
    try {
      Icon ^icon = Icon::FromHandle((IntPtr)sfi.hIcon);
      MemoryStream ^iconstream = gcnew MemoryStream();
      icon->Save(iconstream);
      IconBitmapDecoder ^ibd = \
        gcnew IconBitmapDecoder(iconstream, BitmapCreateOptions::None,
                                BitmapCacheOption::OnLoad);
      this->cache[path] = ibd->Frames[0];
      return ibd->Frames[0];
    } catch (ArgumentException ^) {
      /* nothing */
    } catch (FileNotFoundException ^) {
      /* nothing */
    }

    return nullptr;
  }
#endif /* 0 */
