#ifndef LIBSTRINGOPS_H
#define LIBSTRINGOPS_H

#include <string>

extern "C" void sort_and_replace(std::string& input);
extern "C" int sum_numeric(const std::string& input);
extern "C" bool analyze_length(const std::string& input);

#endif