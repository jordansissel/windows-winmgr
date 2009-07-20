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
using namespace System::Windows::Controls;
using namespace System::Windows::Input;
using namespace System;
using namespace winmgr;

Window ^WindowFromXaml(String ^filename) {
  Stream ^st = File::OpenRead(filename);
  Window ^window = (Window ^)XamlReader::Load(st);
  st->Close();
  return window;
}

void onkeypress(Object ^sender, RoutedEventArgs ^ev) {
  Window ^main = Application::Current->MainWindow;
  TextBox ^t = (TextBox ^)main->FindName("mTextBox");
  main->Title = t->Text;

}

void onloaded(Object ^sender, RoutedEventArgs ^ev) {
  Window ^main = Application::Current->MainWindow;
  main->Title = "Hello there";

  ArrayList ^foo;
  WindowLister ^wl = gcnew WindowLister();
  foo = wl->GetWindows();
  ListBox ^l = (ListBox ^)main->FindName("results");
  l->ItemsSource = foo;
  l->DisplayMemberPath = "title";
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

  Window ^main;

  main = WindowFromXaml("main.xaml");
  main->Height = 400;
  main->Width = 600;
  main->Title = "Testing XAML";
  main->Loaded += gcnew RoutedEventHandler(&onloaded);

  //TextBox ^t = (TextBox ^)main->FindName("mTextBox");
  //t->KeyDown += gcnew KeyEventHandler(&onkeypress);
  //t->TextInput += &onkeypress;

  return (gcnew Application())->Run(main);
}


