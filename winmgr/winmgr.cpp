// winmgr.cpp : main project file.

#include "stdafx.h"
#include "WindowItem.h"
#include "WindowLister.h"
#include "WindowSearcher.h"
#include "resource.h"
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
using namespace System::Xml;
using namespace System::Resources;
using namespace System::Reflection;
using namespace System::Text::RegularExpressions;
using namespace winmgr;

ref class Test {
public:
  property String ^title;
};

ref class WindowManager {
  public:
    WindowSearcher ^wsearch;
    WindowManager() {
      this->wsearch = gcnew winmgr::WindowSearcher();
    }

    Window ^WindowFromXaml(String ^xaml) {
      XmlTextReader ^input = gcnew XmlTextReader(gcnew StringReader(xaml));
		//ResourceManager ^rm = gcnew ResourceManager("", Assembly::GetExecutingAssembly());
	  //Stream ^input = rm->GetStream("main.xaml");
		Window ^window = (Window ^)XamlReader::Load(input);
      //Window ^window = (Window ^)XamlReader::Load(input);
      input->Close();
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

      ItemsControl ^l = (ItemsControl ^)main->FindName("results");
      l->ItemsSource = this->wsearch->filter(input->Text);
    }

    void onkeypress(Object ^sender, KeyEventArgs ^ev) {
      if (ev->Key == Key::Return) {
        TextBox ^input = (TextBox ^)sender;
        ArrayList ^windows = this->wsearch->filter(input->Text);
        //Activate the window of the first item in the list
		if (windows->Count > 0) {
          ((WindowItem ^)windows[0])->activate();
		}

      }
    }

    int start() {
      Window ^main;
      main = WindowFromXaml(MAIN_XAML);
      main->Height = 400;
      main->Width = 600;
      main->Title = "Testing XAML";

      main->Loaded += gcnew RoutedEventHandler(this, &WindowManager::onloaded);

      TextBox ^input = (TextBox ^)main->FindName("userinput");
      input->TextChanged += gcnew TextChangedEventHandler(this, &WindowManager::ontextinput);

      input->KeyDown += gcnew KeyEventHandler(this, &WindowManager::onkeypress);

      return (gcnew Application())->Run(main);
    }
};

[STAThreadAttribute]
int main(array<System::String ^> ^args) {
  return (gcnew WindowManager())->start();
}
