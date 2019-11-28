#pragma once

#include <string>
#include <vector>

std::wstring KuinStrToWStr(const unsigned char* kuin_str);
unsigned char* WStrToKuinStr(const std::wstring wstr);
std::vector<signed long long> KuinArrayToCppVector(const signed long long* kuin_arr);
std::vector<unsigned char> KuinArrayToCppVector(const unsigned char* kuin_arr);
std::vector<double> KuinArrayToCppVector(const double* kuin_arr);
