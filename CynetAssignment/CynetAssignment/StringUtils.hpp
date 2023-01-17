#pragma once

#include <string>
#include <vector>

class StringUtils
{
public:
    StringUtils() = delete;
    ~StringUtils() = delete;

    static bool isNumber(const std::string& s);
    static std::vector<std::string> SplitString(const std::string& s, char delim);
};

