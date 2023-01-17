#include "Process.hpp"

Process::Process(uint16_t pid) :
    _id(pid),
    _parent_id(),
    _grandparent_id(),
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
    return "PID " + std::to_string(_id);
}

