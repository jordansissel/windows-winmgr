// winmgr.cpp : main project file.

#include "stdafx.h"
#include "WindowItem.h"
#include "WindowLister.h"
#include <stdio.h> /* for snprintf */
#using <mscorlib.dll>

using namespace System::Collections;
using namespace System::IO;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Markup;
using namespace System::Windows;
using namespace System;
using namespace winmgr;

Window ^WindowFromXaml(String ^filename) {
  Stream ^st = File::OpenRead(filename);
  Window ^window = (Window ^)XamlReader::Load(st);
  st->Close();
  return window;
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
  ArrayList ^foo;
  WindowLister ^wl = gcnew WindowLister();
  Window ^main;
  foo = wl->GetWindows();

  main = WindowFromXaml("main.xaml");
  main->Height = 400;
  main->Width = 600;
  main->Title = "Testing XAML";
  return (gcnew Application())->Run(main);
}


