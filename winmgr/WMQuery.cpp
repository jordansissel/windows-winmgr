#include "stdafx.h"
#include "WMQuery.h"

namespace winmgr {
  using namespace System::Text::RegularExpressions;

  WMQuery::WMQuery(String ^query) {
    this->SPLIT_RE = gcnew Regex("\\s+");
    this->query_re_list = gcnew ArrayList();
    this->query_string_list = gcnew ArrayList();

    array<String ^> ^tokens = this->SPLIT_RE->Split(query);
    for (int i = 0; i < tokens->Length; i++) {
      this->query_string_list->Add(tokens[i]);
      this->query_re_list->Add(gcnew Regex(tokens[i],
                                           RegexOptions::IgnoreCase));
    }
  }

  bool WMQuery::is_substring(String ^input) {
    IEnumerator ^i = this->query_string_list->GetEnumerator();
    bool found = true;
    while (i->MoveNext()) {
      String ^s = (String ^)i->Current;
      found = found && input->Contains(s);
      if (!found) {
        break;
      }
    }

    return found;
  }

  bool WMQuery::is_match(String ^input) {
    IEnumerator ^i = this->query_re_list->GetEnumerator();
    bool found = true;
    while (i->MoveNext()) {
      Regex ^re = (Regex ^)i->Current;
      found = found && re->IsMatch(input);
      if (!found) {
        break;
      }
    }

    return found;
  }

}
