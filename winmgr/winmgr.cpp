// winmgr.cpp : main project file.

#include "stdafx.h"
#include "WindowItem.h"
#include "WindowLister.h"
#include "WindowSearcher.h"
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

ref class WindowManager {
  public:
    WindowSearcher ^wsearch;
    WindowManager() {
		this->wsearch = gcnew winmgr::WindowSearcher();
    }

    Window ^WindowFromXaml(String ^filename) {
      Stream ^st = File::OpenRead(filename);
      Window ^window = (Window ^)XamlReader::Load(st);
      st->Close();
      return window;
    }

    void onloaded(Object ^sender, RoutedEventArgs ^ev) {
      Window ^main = Application::Current->MainWindow;
      main->Title = "Hello there";

      this->wsearch->start();

      ItemsControl ^l = (ItemsControl ^)main->FindName("results");
      l->ItemsSource = this->wsearch->windows;

      ((TextBox ^)main->FindName("userinput"))->Focus();
    }

    void ontextinput(Object ^sender, TextChangedEventArgs ^ev) {
      TextBox ^input = (TextBox ^)sender;
      Window ^main = Application::Current->MainWindow;
      main->Title = input->Text;
    }

    int start() {
      Window ^main;

      main = WindowFromXaml("main.xaml");
      main->Height = 400;
      main->Width = 600;
      main->Title = "Testing XAML";

	  /* I want to have the 'loaded' event call this->onloaded(...) */
	  main->Loaded += gcnew RoutedEventHandler(this, &WindowManager::onloaded);

      TextBox ^input = (TextBox ^)main->FindName("userinput");
	  /* Same here, I want to call this->ontextinput */
      input->TextChanged += gcnew TextChangedEventHandler(this, &WindowManager::ontextinput);

      return (gcnew Application())->Run(main);
    }
};

[STAThreadAttribute]
int main(array<System::String ^> ^args) {
  return (gcnew WindowManager())->start();
}


