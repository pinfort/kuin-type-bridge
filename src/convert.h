#pragma once

#include <string>

std::wstring KuinStrToWStr(const unsigned char* kuin_str);
unsigned char* WStrToKuinStr(const std::wstring wstr);
