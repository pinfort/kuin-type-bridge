#include <string>
#include <cstdlib>
#include "common.h"
 
BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
  return TRUE;
}

extern "C" _declspec(dllexport) unsigned char* toKuinStr()
{
	char* native_str = "this is test string";
	for (size_t i = 0; i < strlen(native_str); i++)
	{
		printf("%x ", native_str[i]);
	}
	printf("\n");

	unsigned long long default_ref_cnt_func = 0;
	unsigned long long len = strlen(native_str) * 2;

	unsigned char* tmp_str = (unsigned char*)malloc(sizeof(unsigned char) * strlen(native_str) * 2);
	memset(tmp_str, 0, sizeof(unsigned char) * strlen(native_str) * 2);

	size_t tmp_str_cnt = 0;
	for (size_t i = 0; i < strlen(native_str); i++)
	{
		tmp_str[tmp_str_cnt] = native_str[i];
		tmp_str[tmp_str_cnt + 1] = 0x00;
		tmp_str_cnt += 2;
	}

	size_t result_str_len = 0x10 + sizeof(unsigned char) * (size_t)len;
	unsigned char* result_str = (unsigned char*)(malloc(result_str_len));
	memset(result_str, 0, result_str_len);

	((unsigned long long*)result_str)[0] = default_ref_cnt_func; // 0x00-0x07
	((unsigned long long*)result_str)[1] = strlen(native_str); // 0x08-0x0f

	memcpy(result_str + 0x10, tmp_str, sizeof(unsigned char) * (size_t)len);
	free(tmp_str);
	for (size_t i = 0; i < len; i++)
	{
		printf("%x ", (result_str + 0x10)[i]);
	}
	printf("\n");

	return result_str;
}
