#pragma once

#include <cstdint>
#include <string>
#include <filesystem>

#include "File.hpp"

class Process
{
public:
    explicit Process(uint16_t pid);
    virtual ~Process() = default;

    std::string Serialize() const;

private:
    // TODO (ASK):
    // read cmdline from /proc/[pid]/cmdline (optional: handle zombieness)
    // full path / inode by dereferecing /proc/[pid]/exe
    // fds from /proc/[pid]/fd/
    // /proc/[pid]/stat or status for ppid (pppid can be obtained from parent file), vsize\VmSize (virtual mem size), uid
    static std::filesystem::path get_process_stat_file_path(uint16_t process_id);
    static std::filesystem::path get_process_status_file_path(uint16_t process_id);
    static std::filesystem::path get_process_cmdline_file_path(uint16_t process_id);
    static std::filesystem::path get_process_exe_file_path(uint16_t process_id);
    static std::filesystem::path get_process_fd_dir_path(uint16_t process_id);

    static uint16_t get_parent_id(uint16_t process_id);
    static std::filesystem::path get_file_path(uint16_t parent_id);
    static uint64_t get_process_virtual_memory_size(uint16_t process_id);
    static uint32_t get_process_uid(uint16_t process_id);
    static uint16_t get_open_fds_count(uint16_t process_id);

private:
    uint16_t _id;
    uint16_t _parent_id;
    uint16_t _grandparent_id;
    std::string _command_line;
    File _file_data;
    uint64_t _virtual_memory_size_in_bytes;
    uint32_t _uid;
    uint16_t _open_fds_count;
};

