#include "stdafx.h"
#include "WindowSearcher.h"
#include "WindowLister.h"
#include "WindowItem.h"


namespace winmgr {
  WindowSearcher::WindowSearcher() {
    this->windows = gcnew ArrayList();
  }

  void WindowSearcher::start() { 
    WindowLister ^lister = gcnew WindowLister();
    if (this->windows->Count == 0) {
      this->windows = lister->GetWindows();
    }
  }

  ArrayList ^WindowSearcher::filter(String ^filter) {
    ArrayList ^matches = gcnew ArrayList();
    System::Collections::IEnumerator ^i = \
      this->windows->GetEnumerator();
    ArrayList ^re_list = gcnew ArrayList();

    WMQuery ^query = gcnew WMQuery(filter);

    while (i->MoveNext()) {
      WindowItem ^wi = (WindowItem ^)(i->Current);
      if (wi->matches(query)) {
        matches->Add(wi);
      }
    }

    return matches;
  }


  void WindowSearcher::end() { 
    /* nothing yet */
  }
}
