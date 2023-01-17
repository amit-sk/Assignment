#include <fstream>
#include <cassert>

#include <iostream> // TODO (ASK) remove

#include "StringUtils.hpp"
#include "Process.hpp"

Process::Process(uint16_t pid) :
    _id(pid),
    _parent_id(get_parent_id(pid)),
    _grandparent_id(get_parent_id(_parent_id)),
    _command_line(),
    _file_name(),
    _file_path(),
    _file_size(),
    _file_inode(),
    _virtual_memory_size(),
    _uid(),
    _open_fds_count()
{}

std::string Process::Serialize() const
{
    return "PID " + std::to_string(_id) +
        " PPID " + std::to_string(_parent_id) +
        " PPPID " + std::to_string(_grandparent_id);
}

std::filesystem::path Process::get_process_stat_file_path(uint16_t process_id)
{
    return std::filesystem::path("/proc") / std::to_string(process_id) / "stat";
}

uint16_t Process::get_parent_id(uint16_t process_id)
{
    std::filesystem::path process_stat_file_path(get_process_stat_file_path(process_id));

    if (std::filesystem::exists(process_stat_file_path))
    {
        std::string data( 0xFFFF, '\0' );
        std::ifstream(process_stat_file_path, std::ios::binary).read(&data[0], data.size());
        std::vector<std::string> process_stat = StringUtils::SplitString(data, ' ');
        assert(process_stat.size() >= 4);

        // location of pid in file
        std::string ppid(process_stat.at(3));
        return static_cast<uint16_t>(std::stoi(ppid));
    }
    return 0; // marker for invalid pid
}

