#pragma once

#include <windows.h>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;


namespace winmgr {

  /// <summary>
  /// Summary for WindowItem
  /// </summary>
  public ref class WindowItem :  public System::ComponentModel::Component
  {
  public:
    property String^ title;
      HWND hwnd;

    WindowItem(void)
    {
      InitializeComponent();  
    }
    WindowItem(System::ComponentModel::IContainer ^container)
    {
      /// <summary>
      /// Required for Windows.Forms Class Composition Designer support
      /// </summary>

      container->Add(this);
      InitializeComponent();
    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~WindowItem()
    {
      if (components)
      {
        delete components;
      }
    }

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      components = gcnew System::ComponentModel::Container();
    }
#pragma endregion
  };
}
