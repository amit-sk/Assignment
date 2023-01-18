#include <fstream>
#include <cassert>

#include <iostream> // TODO (ASK) remove

#include "StringUtils.hpp"
#include "Process.hpp"

Process::Process(uint16_t pid) :
    _id(pid),
    _parent_id(get_parent_id(pid)),
    _grandparent_id(get_parent_id(_parent_id)),
    _command_line(StringUtils::read_from_file(get_process_cmdline_file_path(pid), 0x200000)),
    _file_name(),
    _file_path(),
    _file_size(),
    _file_inode(),
    _virtual_memory_size(),
    _uid(),
    _open_fds_count()
{
    //std::cout << StringUtils::read_from_file("/bad/path", 10) << '\n';
}

std::string Process::Serialize() const
{
    return "PID " + std::to_string(_id) +
        " PPID " + std::to_string(_parent_id) +
        " PPPID " + std::to_string(_grandparent_id) +
        " cmdline: " + _command_line;
}

std::filesystem::path Process::get_process_stat_file_path(uint16_t process_id)
{
    return std::filesystem::path("/proc") / std::to_string(process_id) / "stat";
}

std::filesystem::path Process::get_process_cmdline_file_path(uint16_t process_id)
{
    return std::filesystem::path("/proc") / std::to_string(process_id) / "cmdline";
}

uint16_t Process::get_parent_id(uint16_t process_id)
{
    std::filesystem::path process_stat_file_path(get_process_stat_file_path(process_id));

    if (std::filesystem::exists(process_stat_file_path))
    {
        std::string file_data = StringUtils::read_from_file(process_stat_file_path, 0xFFFF);
        std::vector<std::string> process_stat = StringUtils::SplitString(file_data, ' ');
        assert(process_stat.size() >= 4);

        // index 3 is the location of pid in file - see man proc
        std::string ppid(process_stat.at(3));
        return static_cast<uint16_t>(std::stoi(ppid));
    }
    return 0; // marker for invalid pid
}

