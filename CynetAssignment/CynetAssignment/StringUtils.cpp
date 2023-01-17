#include <sstream>
#include <cctype>
#include <algorithm>

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

    while (std::getline(input_stream, token, delim))
    {
        split_tokens.push_back(token);
    }

    return split_tokens;
}

