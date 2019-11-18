#include "common.h"
#include "convert.h"

std::wstring KuinStrToWStr(const unsigned char* kuin_str)
{
	unsigned long long char_len = ((unsigned long long*)kuin_str)[1];
	unsigned long long bit_len = sizeof(wchar_t) * ((unsigned long long*)kuin_str)[1];
	unsigned char* result_str = (unsigned char*)(malloc(bit_len + 1));
	memset(result_str, 0, bit_len + 1);

	memcpy(result_str, (kuin_str + 0x10), (size_t)bit_len);
	((wchar_t*)result_str)[char_len] = '\0';
	return (wchar_t*)result_str;
}

unsigned char* WStrToKuinStr(const std::wstring wstr)
{
	// 詳細不明。とりあえず0
	unsigned long long default_ref_cnt_func = 0;

	// 文字列部分の長さ
	unsigned long long len = sizeof(wchar_t) * wstr.length();

	// メタデータ含む全体の長さ
	size_t result_str_len = 0x10 + (size_t)len;

	// 返すバイト列のメモリ確保
	unsigned char* result_str = (unsigned char*)(malloc(result_str_len));
	memset(result_str, 0, result_str_len);

	// メタデータの書き込み
	((unsigned long long*)result_str)[0] = default_ref_cnt_func; // 0x00-0x07
	((unsigned long long*)result_str)[1] = wstr.length(); // 0x08-0x0f

	// 文字列を返すバイト列に書き込み。
	memcpy(result_str + 0x10, wstr.c_str(), (size_t)len);

	return result_str;
}
