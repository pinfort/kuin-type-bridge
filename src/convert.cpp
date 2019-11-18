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

unsigned char* WStrToKuinStr(std::wstring wstr)
{
	// �ڍוs���B�Ƃ肠����0
	unsigned long long default_ref_cnt_func = 0;

	// �����񕔕��̒���
	unsigned long long len = sizeof(wchar_t) * wstr.length();

	// ���^�f�[�^�܂ޑS�̂̒���
	size_t result_str_len = 0x10 + (size_t)len;

	// �Ԃ��o�C�g��̃������m��
	unsigned char* result_str = (unsigned char*)(malloc(result_str_len));
	memset(result_str, 0, result_str_len);

	// ���^�f�[�^�̏�������
	((unsigned long long*)result_str)[0] = default_ref_cnt_func; // 0x00-0x07
	((unsigned long long*)result_str)[1] = wstr.length(); // 0x08-0x0f

	// �������Ԃ��o�C�g��ɏ������݁B
	memcpy(result_str + 0x10, wstr.c_str(), (size_t)len);

	return result_str;
}
