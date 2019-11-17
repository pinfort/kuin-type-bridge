# Kuin type bridge
Kuinの型とC++の型を相互変換するための関数群です。

# C<char*> to Kuin<[]char>
- 関数名
  - CStrToKuinStr
- 注意事項
  - 現状、UTF-8からUTF-16への変換が不完全であるため、Ascii文字以外はおかしくなります。そのうち直します。

# Cpp<std::string> to Kuin<[]char>
- 関数名
  - CppStrToKuinStr
- 注意事項
  - 現状、UTF-8からUTF-16への変換が不完全であるため、Ascii文字以外はおかしくなります。そのうち直します。

# Kuin<[]char> to Cpp<std::string>
そのうち作ります。
