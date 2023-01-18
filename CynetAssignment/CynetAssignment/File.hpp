#pragma once

#include <cstdint>
#include <string>
#include <filesystem>

struct File
{
public:
    std::filesystem::path path;
    std::string file_name;
    uint64_t size;
    uint64_t inode;

public:
    explicit File(std::filesystem::path _path);
    virtual ~File() = default;

private:
    static uint64_t get_file_size(const std::filesystem::path& path);
    static uint64_t get_file_inode(const std::filesystem::path& path);
};

