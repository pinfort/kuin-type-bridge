#include "common.h"
#include "convert.h"

wchar_t* Utf8CStrToUtf16WStr(const char* utf8_str)
{
	if (utf8_str == NULL)
	{
		return NULL;
	}
	/*for (size_t i = 0; i < strlen(utf8_str); i++)
	{
		printf("%x ", utf8_str[i]);
	}
	printf("\n");*/
	
	int str_utf8_len = (int)strlen(utf8_str);
	size_t utf16_str_len = (size_t)MultiByteToWideChar(CP_UTF8, 0, utf8_str, str_utf8_len, NULL, 0);

	wchar_t* result = (wchar_t*)malloc(sizeof(wchar_t) * (utf16_str_len + 1));
	memset(result, 0, sizeof(wchar_t) * (utf16_str_len + 1));

	if (MultiByteToWideChar(CP_UTF8, 0, utf8_str, str_utf8_len, result, (int)utf16_str_len) != (int)utf16_str_len)
	{
		free(result);
		return NULL;
	}

	//result[utf16_str_len] = L'\0';
	return result;
}

char* WStrToCStr(const wchar_t* wstr)
{
	size_t wstr_len = wcslen(wstr);
	wchar_t* result = (wchar_t*)malloc(sizeof(wchar_t) * (size_t)(wstr_len + 1));
	memset(result, 0, sizeof(wchar_t) * (size_t)(wstr_len + 1));

	result = const_cast<wchar_t*>(wstr);
	result[wstr_len] = L'\0';
	return (char*)result;
}
