
namespace winmgr {
  using namespace System;
  using namespace System::Collections;
  using namespace System::Text::RegularExpressions;

  public ref class WMQuery {
    public:
      ArrayList ^query_re_list;
      ArrayList ^query_string_list;

      WMQuery(String ^query);
      bool is_substring(String ^input);
      bool is_match(String ^input);

    private:
      Regex ^SPLIT_RE;
  };
}
