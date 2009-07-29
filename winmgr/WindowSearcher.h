
namespace winmgr {
  using namespace System;
  using namespace System::Collections;

  public ref class WindowSearcher {
    public:
      ArrayList ^windows;
      WindowSearcher();

      void start();
      ArrayList ^filter(String ^filter);
      void end();
  };
}
