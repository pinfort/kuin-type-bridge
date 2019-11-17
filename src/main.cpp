#include <string>
#include <cstdlib>
#include "common.h"
 
BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
  return TRUE;
}

unsigned char* CStrToKuinStr(char* native_str)
{
	// TODO: printデバッグを消せ
	for (size_t i = 0; i < strlen(native_str); i++)
	{
		printf("%x ", native_str[i]);
	}
	printf("\n");

	// 詳細不明。とりあえず0
	unsigned long long default_ref_cnt_func = 0;

	// UTF-8 UTF-16変換のための一時文字列、メモリ確保
	unsigned char* tmp_str = (unsigned char*)malloc(sizeof(unsigned char) * strlen(native_str) * 2);
	memset(tmp_str, 0, sizeof(unsigned char) * strlen(native_str) * 2);

	// UTF-8 UTF-16変換のために元の文字列一バイトごとに後ろに0x00を挿入
	// TODO: まともなUTF-8 UTF-16変換を使う
	size_t tmp_str_cnt = 0;
	for (size_t i = 0; i < strlen(native_str); i++)
	{
		tmp_str[tmp_str_cnt] = native_str[i];
		tmp_str[tmp_str_cnt + 1] = 0x00;
		tmp_str_cnt += 2;
	}

	// UTF-16変換後の文字列部分の長さ
	unsigned long long len = strlen(native_str) * 2;

	// UTF-16変換後のメタデータ含む全体の長さ
	size_t result_str_len = 0x10 + sizeof(unsigned char) * (size_t)len;

	// 返すバイト列のメモリ確保
	unsigned char* result_str = (unsigned char*)(malloc(result_str_len));
	memset(result_str, 0, result_str_len);

	// メタデータの書き込み
	((unsigned long long*)result_str)[0] = default_ref_cnt_func; // 0x00-0x07
	((unsigned long long*)result_str)[1] = strlen(native_str); // 0x08-0x0f

	// UTF-16変換された文字列を返すバイト列に書き込み。一時文字列はメモリ開放
	memcpy(result_str + 0x10, tmp_str, sizeof(unsigned char) * (size_t)len);
	free(tmp_str);

	// TODO: printデバッグを消せ
	for (size_t i = 0; i < len; i++)
	{
		printf("%x ", (result_str + 0x10)[i]);
	}
	printf("\n");

	return result_str;
}

unsigned char* CppStrToKuinStr(std::string native_str)
{
	return CStrToKuinStr(const_cast<char*>(native_str.c_str()));
}

extern "C" _declspec(dllexport) unsigned char* toKuinStr()
{
	std::string native_str = "this is test string";
	unsigned char* result_str = CppStrToKuinStr(native_str);

	return result_str;
}
