#include <sstream>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <cassert> // TODO (ASK)
#include <iostream> // TODO (ASK)

#include "StringUtils.hpp"

bool StringUtils::isNumber(const std::string &s)
{
    return (not s.empty()) and std::all_of(s.begin(), s.end(), ::isdigit);
}

std::vector<std::string> StringUtils::SplitString(const std::string& s, char delim)
{
    std::string token;
    std::vector<std::string> split_tokens;
    std::istringstream input_stream(s);
    assert(input_stream.good());

    while (std::getline(input_stream, token, delim))
    {
        assert(not input_stream.bad());
        split_tokens.push_back(token);
    }

    return split_tokens;
}

std::string StringUtils::read_from_file(const std::filesystem::path& path, size_t max_read_size)
{
    assert(std::filesystem::exists(path));

    std::string data( max_read_size, '\0' );
    std::ifstream stream(path, std::ios::binary);
    assert(stream.good());

    stream.read(&data[0], data.size());
    assert(not stream.bad());

    return data;
}

