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

#include "mainwindow.h"

ref class WindowManager : Application {
  public:
    WindowSearcher ^wsearch;
    WindowManager() {
      this->Initialize();
    }

    Window ^WindowFromXaml(String ^xaml) {
      XmlTextReader ^input = gcnew XmlTextReader(gcnew StringReader(xaml));
      
      //Stream ^input = File::OpenRead("mainwindow.xaml";)
	  Window ^window = (Window ^)XamlReader::Load(input);

      input->Close();
      return window;
    }

    void onloaded(Object ^sender, RoutedEventArgs ^ev) {
      ////main->Title = "Hello there";

      this->wsearch->start();

      ItemsControl ^l = (ItemsControl ^)this->MainWindow->FindName("results");
      l->ItemsSource = this->wsearch->windows;
      ((TextBox ^)this->MainWindow->FindName("userinput"))->Focus();
    }

    void ontextinput(Object ^sender, TextChangedEventArgs ^ev) {
      TextBox ^input = (TextBox ^)sender;
      ItemsControl ^l = (ItemsControl ^)this->MainWindow->FindName("results");
      l->ItemsSource = this->wsearch->filter(input->Text);
    }

    void input_onkeypress(Object ^sender, KeyEventArgs ^ev) {
      if (ev->Key == Key::Return) {
        TextBox ^input = (TextBox ^)sender;
        ArrayList ^windows = this->wsearch->filter(input->Text);
        //Activate the window of the first item in the list
        if (windows->Count > 0) {
          ((WindowItem ^)windows[0])->activate();
        }
        ev->Handled = true;
      } else if (ev->Key == Key::Escape) {
        /* Destroy window */
        //Window ^main = Application::Current->MainWindow;
        //main->Close();
      }
    }

    void window_onkeypress(Object ^sender, KeyEventArgs ^ev) {
      if (ev->Key == Key::Escape) {
        /* Destroy window */
        this->MainWindow->Close();
      }
    }

	void app_onstartup(Object ^sender, StartupEventArgs ^ev) {
		this->MainWindow->Show();
	}

    void Initialize() {
      this->wsearch = gcnew winmgr::WindowSearcher();
      this->MainWindow = WindowFromXaml(MAINWINDOW_XAML);
      this->MainWindow->Height = 200;
      this->MainWindow->Width = 600;
      //main->Title = "Testing XAML";
      this->MainWindow->Loaded += gcnew RoutedEventHandler(this, &WindowManager::onloaded);

      TextBox ^input = (TextBox ^)this->MainWindow->FindName("userinput");
      input->TextChanged += gcnew TextChangedEventHandler(this, &WindowManager::ontextinput);

      input->KeyDown += gcnew KeyEventHandler(this, &WindowManager::input_onkeypress);
      this->MainWindow->KeyDown += gcnew KeyEventHandler(this, &WindowManager::window_onkeypress);
	  this->Startup += gcnew StartupEventHandler(this, &WindowManager::app_onstartup);
    }
};

[STAThreadAttribute]
int main(array<System::String ^> ^args) {
  return (gcnew WindowManager())->Run();
}
