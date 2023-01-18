#include <sys/stat.h>
#include <cassert>
#include <algorithm>

#include "File.hpp"

File::File(std::filesystem::path _path) :
    path(std::move(_path)),
    file_name(path.filename()),
    size(get_file_size(path)),
    inode(get_file_inode(path))
{}

uint64_t File::get_file_size(const std::filesystem::path& path)
{
    if (std::filesystem::exists(path))
    {
        return std::filesystem::file_size(path);
    }
    return 0;
}

uint64_t File::get_file_inode(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path))
    {
        return 0;
    }

    struct stat s{0};
    assert(stat(path.c_str(), &s) == 0);
    return s.st_ino;
}

