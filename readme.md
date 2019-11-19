# Kuin type bridge

Kuinの型とC++の型を相互変換するための関数群です。

## Info

これはVisual Studio 2019で作成されたプロジェクトです。
プロジェクトは静的ライブラリ用に設定されています。静的ライブラリとして利用する場合、リリースにバイナリをおいていますので、それを利用することができます。

そのほか、自由にビルドして様々な形態として利用できます。

## Functions

### ~~Cpp<char*> to Kuin<[]char>~~

削除されました。

### Cpp\<std::wstring> to Kuin<[]char>

- 定義
  - unsigned char* WStrToKuinStr(const std::wstring wstr);
- 関数名
  - WStrToKuinStr
- 注意事項
  - 入力の型がstd::stringからstd::wstringに変更になっています。
  - 入力の型の変更に伴い関数名が変更されています。

### Kuin<[]char> to Cpp\<std::wstring>

- 定義
  - std::wstring KuinStrToWStr(const unsigned char* kuin_str);
- 関数名
  - KuinStrToWStr
- 注意事項
  - 出力の型はstd::wstringです。

## LICENSE

くいなちゃんライセンス
