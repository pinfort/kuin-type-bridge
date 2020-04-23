#pragma once

#include <string>
#include <vector>

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

	unsigned long long getLen();
	unsigned long long getDefaultRefCntFunc();
	void* getBody();
	unsigned char* getRaw();
private:
	unsigned long long default_ref_cnt_func;
	unsigned long long len;
	void* body;
};

std::wstring KuinStrToWStr(const unsigned char* kuin_str);
unsigned char* WStrToKuinStr(const std::wstring wstr, unsigned long long default_ref_cnt_func);
std::vector<signed long long> KuinArrayToCppVector(const signed long long* kuin_arr);
std::vector<unsigned char> KuinArrayToCppVector(const unsigned char* kuin_arr);
std::vector<double> KuinArrayToCppVector(const double* kuin_arr);
unsigned char* CppVectorToKuinArray(const std::vector<unsigned char> cpp_vector, unsigned long long default_ref_cnt_func);
