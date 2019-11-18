# Kuin type bridge
Kuinの型とC++の型を相互変換するための関数群です。

## ~~Cpp<char*> to Kuin<[]char>~~
削除されました。

## Cpp\<std::wstring> to Kuin<[]char>
- 定義
  - unsigned char* WStrToKuinStr(const std::wstring wstr);
- 関数名
  - WStrToKuinStr
- 注意事項
  - 入力の型がstd::stringからstd::wstringに変更になっています。
  - 入力の型の変更に伴い関数名が変更されています。

## Kuin<[]char> to Cpp\<std::string>
- 定義
  - std::wstring KuinStrToWStr(const unsigned char* kuin_str);
- 関数名
  - KuinStrToWStr
- 注意事項
  - 出力の型はstd::wstringです。
