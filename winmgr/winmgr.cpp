// winmgr.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include "WindowItem.h"
#include <stdio.h> /* for snprintf */
#using <mscorlib.dll>

using namespace winmgr;
using namespace System;
using namespace System::Collections;
using namespace System::Runtime::InteropServices;

// A delegate type.
delegate BOOL CallBack(HWND hwnd, LPARAM lparam);


ref class MyTest {
  public:
    ArrayList ^windows;

    MyTest() {
      windows = gcnew ArrayList();
    }

    BOOL proc(HWND hwnd, LPARAM lparam) {
      wchar_t data[200];
      WindowItem ^wi = gcnew WindowItem();
      wi->hwnd = hwnd;
      GetWindowText(hwnd, data, 200);

      if (data[0] != NULL) {
        wi->title = gcnew String(data);
        this->windows->Add(wi);
      }
      return TRUE;
    }
};

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
  ArrayList ^foo;
  // Enabling Windows XP visual effects before any controls are created
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false); 

  //f->dataGridView1->DataSource = foo;

  OutputDebugStringA("Hello\n");
  MyTest ^mt = gcnew MyTest();
  CallBack ^cb = gcnew CallBack(mt, &MyTest::proc);
  pin_ptr<CallBack^> pinner = &cb;
  IntPtr cbptr = Marshal::GetFunctionPointerForDelegate(cb);
  WNDENUMPROC enumproc = static_cast<WNDENUMPROC>(cbptr.ToPointer());
  EnumWindows(enumproc, 0);

  Form1 ^f = gcnew Form1(mt->windows);
  Application::Run(f);

  return 0;
}

