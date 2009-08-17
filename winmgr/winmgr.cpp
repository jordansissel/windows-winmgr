// winmgr.cpp : main project file.

#include "stdafx.h"
#include "WindowItem.h"
#include "WindowLister.h"
#include "WindowSearcher.h"
#include "resource.h"
#include "searchwin.h" /* comes from searchwin.xaml */

#include <stdio.h> /* for snprintf */
#using <mscorlib.dll>

using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::Windows::Threading;
using namespace System::IO;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Markup;
using namespace System::Windows::Interop;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Input;       
using namespace System;
using namespace System::Xml;
using namespace System::Resources;
using namespace System::Reflection;
using namespace System::Text::RegularExpressions;
using namespace winmgr;

delegate void VoidDelegate();

public ref class WindowManager : Application {
  public:
    WindowSearcher ^wsearch;
    BackgroundWorker ^hotkeyworker;
    BackgroundWorker ^windowupdater;

    WindowManager() {
      this->Initialize();
    }

    Window ^WindowFromXaml(String ^xaml) {
      XmlTextReader ^input = gcnew XmlTextReader(gcnew StringReader(xaml));
      Window ^window = (Window ^)XamlReader::Load(input);
      input->Close();
      return window;
    }

    void activate() {
      ItemsControl ^l = (ItemsControl ^)this->MainWindow->FindName("results");
      l->ItemsSource = this->wsearch->windows;
      TextBox ^input = ((TextBox ^)this->MainWindow->FindName("userinput"));
      input->Text = "";

      this->MainWindow->Top = -100;
      this->MainWindow->Show();
      this->MainWindow->Activate();
      this->MainWindow->Topmost = true; /* Set always on top */
      this->MainWindow->Focus();

      input->Focus();
      //BackgroundWorker ^animate_in = gcnew BackgroundWorker();
      //animate_in->DoWork += \
        //gcnew DoWorkEventHandler(this, &WindowManager::BackgroundAnimateIn);
      //animate_in->RunWorkerAsync();

      //System::Windows::Media::Animatio
      this->MainWindow->Top = 0;
    }	
    void onloaded(Object ^sender, RoutedEventArgs ^ev) {
      /* Nothing */
    }

    void input_ontextinput(Object ^sender, TextChangedEventArgs ^ev) {
      TextBox ^input = (TextBox ^)sender;
      ItemsControl ^l = (ItemsControl ^)this->MainWindow->FindName("results");
      try {
        l->ItemsSource = this->wsearch->filter(input->Text);
      } catch (ArgumentException ^) {
        /* regexp compilation error, ignore it and do not alter the
         * filtered view. */
      }
    }

    void input_onkeypress(Object ^sender, KeyEventArgs ^ev) {
      if (ev->Key == Key::Return) {
        TextBox ^input = (TextBox ^)sender;

        /* Special handle 'quit' string for exiting the program */
        if (input->Text == "quit") {
          this->MainWindow->Hide();
          exit(0);
          return;
        }

        ArrayList ^windows = this->wsearch->filter(input->Text);
        //Activate the window of the first item in the list
        if (windows->Count > 0) {
          ((WindowItem ^)windows[0])->activate();
        }
        ev->Handled = true;
        this->MainWindow->Hide();
      }
    }

    void window_onkeypress(Object ^sender, KeyEventArgs ^ev) {
      if (ev->Key == Key::Escape) {
        /* Destroy window */
        this->MainWindow->Hide();
      }
    }

    void window_onmousedown(Object ^sender, MouseButtonEventArgs ^ev) {
      //if (ev->ChangedButton == MouseButton::Left) {
        //this->MainWindow->DragMove();
      //}
    }

    void app_onstartup(Object ^sender, StartupEventArgs ^ev) {
      /* Unused for the moment. */
    }


    void Initialize() {
      this->wsearch = gcnew winmgr::WindowSearcher();
      this->MainWindow = WindowFromXaml(SEARCHWIN_XAML);
      this->MainWindow->Left = 0;
      this->MainWindow->Top = 0;
      //this->MainWindow->Height = 200;
      //this->MainWindow->Width = 600;
      this->MainWindow->Loaded += gcnew RoutedEventHandler(this, &WindowManager::onloaded);

      TextBox ^input = (TextBox ^)this->MainWindow->FindName("userinput");
      input->TextChanged += \
        gcnew TextChangedEventHandler(this, &WindowManager::input_ontextinput);
      input->KeyDown += \
        gcnew KeyEventHandler(this, &WindowManager::input_onkeypress);
      this->MainWindow->KeyDown += \
        gcnew KeyEventHandler(this, &WindowManager::window_onkeypress);
      this->MainWindow->MouseDown += \
        gcnew MouseButtonEventHandler(this, &WindowManager::window_onmousedown);
	  this->MainWindow->Mouse 
      this->Startup += \
        gcnew StartupEventHandler(this, &WindowManager::app_onstartup);

      this->hotkeyworker = gcnew BackgroundWorker();
      this->hotkeyworker->DoWork += \
        gcnew DoWorkEventHandler(this, &WindowManager::BackgroundHotKeyHandler);
      this->hotkeyworker->RunWorkerAsync();

      this->windowupdater = gcnew BackgroundWorker();
      this->windowupdater->DoWork += \
        gcnew DoWorkEventHandler(this, &WindowManager::BackgroundWindowUpdater);
      this->windowupdater->RunWorkerAsync();
    }

    void BackgroundWindowUpdater(Object ^sender, DoWorkEventArgs ^ev) {
      /* Really, we should listen for window creation/destruction.
       * and for window title changes */
      while (true) {
        this->wsearch->start();
        ::Sleep(2000);
      }
    }

    void BackgroundAnimateIn(Object ^sender, DoWorkEventArgs ^ev) {
      while (this->MainWindow->Top < 0) {
        this->MainWindow->Top += 1;
        ::Sleep(1);
      }
    }

    void BackgroundHotKeyHandler(Object ^sender, DoWorkEventArgs ^ev) {
      tagMSG msg = {0};
      BackgroundWorker ^bw = (BackgroundWorker ^)sender;
      RegisterHotKey(NULL, 1, MOD_ALT, VK_SPACE);

      while (GetMessage(&msg, NULL, 0, 0) != 0) { 
        if (msg.message == WM_HOTKEY) {
          VoidDelegate ^vd = gcnew VoidDelegate(this, &WindowManager::activate);
          this->Dispatcher->Invoke(DispatcherPriority::Normal, vd);
        }
      }
      UnregisterHotKey(NULL, 1);
    }
};

[STAThreadAttribute]
int main(array<System::String ^> ^args) {
  WindowManager ^wm = gcnew WindowManager();
  return wm->Run();
}
