#pragma once

#include "WindowItem.h"
namespace winmgr {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace System::Text::RegularExpressions;

  public ref class Form1 : public System::Windows::Forms::Form {
    public:
      Form1(ArrayList ^data) {
        InitializeComponent();

        this->original_list = this->current_list = data;
        this->dataGridView1->DataSource = this->current_list;
      }

    protected:
      ArrayList ^original_list;
      ArrayList ^current_list;

      ~Form1() {
        if (components) {
          delete components;
        }
      }
    private:
      System::Windows::Forms::SplitContainer^  splitContainer1;
      System::Windows::Forms::DataGridView^  dataGridView1;
      System::Windows::Forms::RichTextBox^  richTextBox2;
      System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
      void InitializeComponent(void) {
               this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
               this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
               this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
               this->splitContainer1->Panel1->SuspendLayout();
               this->splitContainer1->Panel2->SuspendLayout();
               this->splitContainer1->SuspendLayout();
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
               this->SuspendLayout();
               // 
               // splitContainer1
               // 
               this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
               this->splitContainer1->Location = System::Drawing::Point(0, 0);
               this->splitContainer1->Name = L"splitContainer1";
               this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
               // 
               // splitContainer1.Panel1
               // 
               this->splitContainer1->Panel1->Controls->Add(this->dataGridView1);
               // 
               // splitContainer1.Panel2
               // 
               this->splitContainer1->Panel2->Controls->Add(this->richTextBox2);
               this->splitContainer1->Size = System::Drawing::Size(430, 264);
               this->splitContainer1->SplitterDistance = 235;
               this->splitContainer1->TabIndex = 0;
               // 
               // dataGridView1
               // 
               this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
               this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
               this->dataGridView1->Location = System::Drawing::Point(0, 0);
               this->dataGridView1->MultiSelect = false;
               this->dataGridView1->Name = L"dataGridView1";
               this->dataGridView1->ReadOnly = true;
               this->dataGridView1->Size = System::Drawing::Size(430, 235);
               this->dataGridView1->TabIndex = 0;
               // 
               // richTextBox2
               // 
               this->richTextBox2->Dock = System::Windows::Forms::DockStyle::Fill;
               this->richTextBox2->Location = System::Drawing::Point(0, 0);
               this->richTextBox2->Multiline = false;
               this->richTextBox2->Name = L"richTextBox2";
               this->richTextBox2->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
               this->richTextBox2->Size = System::Drawing::Size(430, 25);
               this->richTextBox2->TabIndex = 1;
               this->richTextBox2->Text = L"";
               this->richTextBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::richTextBox2_KeyPress);
               this->richTextBox2->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox2_TextChanged);
               // 
               // Form1
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(430, 264);
               this->Controls->Add(this->splitContainer1);
               this->DoubleBuffered = true;
               this->Name = L"Form1";
               this->Text = L"winmgr";
               this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
               this->splitContainer1->Panel1->ResumeLayout(false);
               this->splitContainer1->Panel2->ResumeLayout(false);
               this->splitContainer1->ResumeLayout(false);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
               this->ResumeLayout(false);

             }
#pragma endregion
    private: 

             System::Void richTextBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
               // this->richTextBox2->Text;
               Regex ^wordsep = gcnew Regex("\\s+");
               String ^search = this->richTextBox2->Text;
               array<String^> ^tokens = wordsep->Split(search);
               this->current_list = (ArrayList ^)this->original_list->Clone();

               for (int i = 0; i < tokens->Length; i++) {
                 try {
                   Regex ^re = gcnew Regex(tokens[i], RegexOptions::IgnoreCase);
                   IEnumerator ^i = this->current_list->GetEnumerator();
                   ArrayList ^to_remove = gcnew ArrayList();
                   while (i->MoveNext()) {
                     WindowItem ^wi = safe_cast<WindowItem^>(i->Current);
                     if (! re->IsMatch(wi->title)) {
                       //this->current_list->Remove(wi);
                       to_remove->Add(wi);
                     }
                   }

                   i = to_remove->GetEnumerator();
                   while (i->MoveNext()) {
                     WindowItem ^wi = safe_cast<WindowItem^>(i->Current);
                     this->current_list->Remove(wi);
                   }

                   if (this->current_list->Count == 0) {
                     this->dataGridView1->DataSource = NULL;
                     /* XXX: show 'no matches found' */
                   } else {
                     this->dataGridView1->DataSource = this->current_list;
                   }
                 } catch (System::ArgumentException ^e) {
                   /* regex error, ignore */
                 }
               }

             }
    private: System::Void richTextBox2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
               if (e->KeyChar == (wchar_t)Keys::Return) {
                 //e->Handled = true;
                 WindowItem ^wi = (WindowItem ^)(this->current_list)[0];
                 /* Learned from AUtoIt3's source code and MSDN docs.
                  * According to docs, SetForegroundWindow will fail if the target hwnd's thread is not attached. */
                 DWORD mythread, curthread, newthread;
                 HWND curfg;
                 curfg = GetForegroundWindow();
                 if (!curfg) {
                   curfg = FindWindowA("Shell_TrayWnd", NULL);
                 }

                 if (IsIconic(wi->hwnd)) {
                   ShowWindow(wi->hwnd, SW_RESTORE);
                 }

                 curthread = GetWindowThreadProcessId(curfg, NULL);
                 mythread = GetCurrentThreadId();
                 newthread = GetWindowThreadProcessId(wi->hwnd, NULL);

                 AttachThreadInput(mythread, newthread, TRUE);
                 AttachThreadInput(mythread, curthread, TRUE);
                 AttachThreadInput(curthread, newthread, TRUE);

                 AnimateWindow(wi->hwnd, 200, AW_ACTIVATE | AW_BLEND);
                 SetForegroundWindow(wi->hwnd);

                 AttachThreadInput(mythread, newthread, FALSE);
                 AttachThreadInput(mythread, curthread, FALSE);
                 AttachThreadInput(curthread, newthread, FALSE);
               }
             }
    private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
               this->richTextBox2->Focus();
             }
  };
}

