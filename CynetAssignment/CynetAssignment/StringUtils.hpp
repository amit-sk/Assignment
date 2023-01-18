#pragma once

#include <string>
#include <vector>
#include <filesystem>

class StringUtils
{
public:
    StringUtils() = delete;
    ~StringUtils() = delete;

    static bool isNumber(const std::string& s);
    static std::vector<std::string> SplitString(const std::string& s, char delim);

    static std::string read_from_file(const std::filesystem::path& path, size_t max_read_size);
};

