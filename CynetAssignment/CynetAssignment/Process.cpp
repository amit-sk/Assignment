#include <fstream>
#include <cassert>
#include <cerrno>

#include <iostream> // TODO (ASK) remove

#include "StringUtils.hpp"
#include "Process.hpp"

Process::Process(uint16_t pid) :
    _id(pid),
    _parent_id(get_parent_id(pid)),
    _grandparent_id(get_parent_id(_parent_id)),
    _command_line(StringUtils::read_from_file(get_process_cmdline_file_path(pid), 0x200000)),
    _file_data(get_file_path(pid)),
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
        " cmdline (" + _command_line +
        ") file path (" + std::string(_file_data.path) +
        ") file name (" + _file_data.file_name +
        ") file size " + std::to_string(_file_data.size) +
        " file inode " + std::to_string(_file_data.inode);
}

std::filesystem::path Process::get_process_stat_file_path(uint16_t process_id)
{
    return std::filesystem::path("/proc") / std::to_string(process_id) / "stat";
}

std::filesystem::path Process::get_process_cmdline_file_path(uint16_t process_id)
{
    return std::filesystem::path("/proc") / std::to_string(process_id) / "cmdline";
}

std::filesystem::path Process::get_process_exe_file_path(uint16_t process_id)
{
    return std::filesystem::path("/proc") / std::to_string(process_id) / "exe";
}

uint16_t Process::get_parent_id(uint16_t process_id)
{
    const std::filesystem::path process_stat_file_path(get_process_stat_file_path(process_id));

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

std::filesystem::path Process::get_file_path(uint16_t process_id)
{
    const std::filesystem::path exe_file_path = get_process_exe_file_path(process_id);
    if (std::filesystem::is_symlink(exe_file_path))
    {
        try
        {
            return std::filesystem::read_symlink(exe_file_path);
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            if (e.code().value() == ENOENT)
            {
                // The exe file is a symlink to a non-existing file in case of kernel thread processes -
                // which truely don't have exe files on the filesystem.
                return "";
            }
            throw;
        }
    }
    return "";
}

