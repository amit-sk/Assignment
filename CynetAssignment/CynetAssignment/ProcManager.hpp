#pragma once

#include <filesystem>
#include <mutex>

class ProcManager
{
    // TODO (ASK) static singleton
private:
    constexpr static char proc_directory_path_name[] = "/proc/";
    const std::filesystem::path proc_direcory_path{ proc_directory_path_name };

public:
    ProcManager() = default;
    virtual ~ProcManager() = default;

    void run();

private:
    void RefreshProcessList();
    void SleepSomeTime();
};

