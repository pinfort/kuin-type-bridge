#include "common.h"
#include "kuin_type_bridge.h"

class KuinArray
{
public:
	KuinArray(void* kuin_arr)
	{
		default_ref_cnt_func = ((unsigned long long*)kuin_arr)[0];
		len = ((unsigned long long*)kuin_arr)[1];

		body = (unsigned char*)kuin_arr + 0x10;
	}

	KuinArray(unsigned long long len, unsigned long long default_ref_cnt_func, void* body)
	{
		KuinArray::len = len;
		KuinArray::default_ref_cnt_func = default_ref_cnt_func;
		KuinArray::body = body;
	}

	unsigned long long getLen()
	{
		return len;
	}

	unsigned long long getDefaultRefCntFunc()
	{
		return default_ref_cnt_func;
	}

	void* getBody()
	{
		return body;
	}

	unsigned char* getRaw()
	{
		// メタデータ含む全体の長さ
		size_t result_len = 0x10 + (size_t)len;

		// 返すバイト列のメモリ確保
		unsigned char* result = (unsigned char*)(malloc(result_len));
		memset(result, 0, result_len);

		// メタデータの書き込み
		((unsigned long long*)result)[0] = default_ref_cnt_func; // 0x00-0x07
		((unsigned long long*)result)[1] = len; // 0x08-0x0f

		memcpy(result + 0x10, body, (size_t)len);

		return result;
	}

private:
	unsigned long long default_ref_cnt_func;
	unsigned long long len;
	void* body;
};

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
	size_t result_str_len = 0x10 + (size_t)len + 1;

	// 返すバイト列のメモリ確保
	unsigned char* result_str = (unsigned char*)(malloc(result_str_len));
	memset(result_str, 0, result_str_len);

	// メタデータの書き込み
	((unsigned long long*)result_str)[0] = default_ref_cnt_func; // 0x00-0x07
	((unsigned long long*)result_str)[1] = wstr.length(); // 0x08-0x0f

	// 文字列を返すバイト列に書き込み。
	memcpy(result_str + 0x10, wstr.c_str(), (size_t)len);

	// Null終端させる
	((unsigned char*)(result_str + 0x10 + len + 1))[0] = '\0';

	return result_str;
}

std::vector<signed long long> KuinArrayToCppVector(const signed long long* kuin_arr)
{
	KuinArray kuin_arr_obj = KuinArray((void*)kuin_arr);

	unsigned long long arr_len = kuin_arr_obj.getLen();

	std::vector<signed long long> result_arr(arr_len);

	signed long long* body_arr = (signed long long*)kuin_arr_obj.getBody();

	for (size_t i = 0; i < arr_len; i++)
	{
		result_arr[i] = body_arr[i];
	}

	return result_arr;
}

std::vector<unsigned char> KuinArrayToCppVector(const unsigned char* kuin_arr)
{
	KuinArray kuin_arr_obj = KuinArray((void*)kuin_arr);

	unsigned long long arr_len = kuin_arr_obj.getLen();

	std::vector<unsigned char> result_arr(arr_len);

	unsigned char* body_arr = (unsigned char*)kuin_arr_obj.getBody();

	for (size_t i = 0; i < arr_len; i++)
	{
		result_arr[i] = body_arr[i];
	}

	return result_arr;
}

std::vector<double> KuinArrayToCppVector(const double* kuin_arr)
{
	KuinArray kuin_arr_obj = KuinArray((void*)kuin_arr);

	unsigned long long arr_len = kuin_arr_obj.getLen();

	std::vector<double> result_arr(arr_len);

	double* body_arr = (double*)kuin_arr_obj.getBody();

	for (size_t i = 0; i < arr_len; i++)
	{
		result_arr[i] = body_arr[i];
	}

	return result_arr;
}

std::vector<std::wstring> KuinArrayToCppVector(const unsigned char** kuin_arr)
{
	KuinArray kuin_arr_obj = KuinArray((void*)kuin_arr);

	unsigned long long arr_len = kuin_arr_obj.getLen();

	std::vector<std::wstring> result_arr(arr_len);

	void** body_str_ptr = (void**)kuin_arr_obj.getBody();

	for (size_t i = 0; i < arr_len; i++)
	{
		std::wstring str = KuinStrToWStr((unsigned char*)*body_str_ptr);
		result_arr[i] = str;

		body_str_ptr++;
	}

	return result_arr;
}

unsigned char* CppVectorToKuinArray(const std::vector<unsigned char> cpp_vector)
{
	unsigned long long len = cpp_vector.size();

	// 詳細不明。とりあえず0
	unsigned long long default_ref_cnt_func = 0;

	// 返すバイト列のメモリ確保
	unsigned char* ptr = (unsigned char*)(malloc(sizeof(unsigned char) * (cpp_vector.size() + 1)));

	for (size_t i = 0; i < cpp_vector.size(); i++)
	{
		ptr[i] = cpp_vector[i];
	}
	// TODO: そもそもnull終端されていた場合？
	ptr[cpp_vector.size()] = '\0';
	KuinArray result_arr(len, default_ref_cnt_func, ptr);
	return result_arr.getRaw();
}
