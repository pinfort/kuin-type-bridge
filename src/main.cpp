#include <cstdlib>
#include <clocale>
#include "common.h"
#include "convert.h"

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
  return TRUE;
}

extern "C" _declspec(dllexport) unsigned char* toKuinStr(unsigned char* input)
{
	setlocale(LC_ALL, "Japanese");

	// 入力テスト
	wprintf(L"%ls\n", KuinStrToWStr(input).c_str());

	// 出力テスト
	std::wstring native_str = L"日本語だよ";
	return WStrToKuinStr(native_str);
}
