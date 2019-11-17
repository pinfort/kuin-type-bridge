#include <string>
#include <cstdlib>
#include "common.h"
 
BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
  return TRUE;
}

unsigned char* CStrToKuinStr(char* native_str)
{
	// TODO: print�f�o�b�O������
	for (size_t i = 0; i < strlen(native_str); i++)
	{
		printf("%x ", native_str[i]);
	}
	printf("\n");

	// �ڍוs���B�Ƃ肠����0
	unsigned long long default_ref_cnt_func = 0;

	// UTF-8 UTF-16�ϊ��̂��߂̈ꎞ������A�������m��
	unsigned char* tmp_str = (unsigned char*)malloc(sizeof(unsigned char) * strlen(native_str) * 2);
	memset(tmp_str, 0, sizeof(unsigned char) * strlen(native_str) * 2);

	// UTF-8 UTF-16�ϊ��̂��߂Ɍ��̕������o�C�g���ƂɌ���0x00��}��
	// TODO: �܂Ƃ���UTF-8 UTF-16�ϊ����g��
	size_t tmp_str_cnt = 0;
	for (size_t i = 0; i < strlen(native_str); i++)
	{
		tmp_str[tmp_str_cnt] = native_str[i];
		tmp_str[tmp_str_cnt + 1] = 0x00;
		tmp_str_cnt += 2;
	}

	// UTF-16�ϊ���̕����񕔕��̒���
	unsigned long long len = strlen(native_str) * 2;

	// UTF-16�ϊ���̃��^�f�[�^�܂ޑS�̂̒���
	size_t result_str_len = 0x10 + sizeof(unsigned char) * (size_t)len;

	// �Ԃ��o�C�g��̃������m��
	unsigned char* result_str = (unsigned char*)(malloc(result_str_len));
	memset(result_str, 0, result_str_len);

	// ���^�f�[�^�̏�������
	((unsigned long long*)result_str)[0] = default_ref_cnt_func; // 0x00-0x07
	((unsigned long long*)result_str)[1] = strlen(native_str); // 0x08-0x0f

	// UTF-16�ϊ����ꂽ�������Ԃ��o�C�g��ɏ������݁B�ꎞ������̓������J��
	memcpy(result_str + 0x10, tmp_str, sizeof(unsigned char) * (size_t)len);
	free(tmp_str);

	// TODO: print�f�o�b�O������
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
