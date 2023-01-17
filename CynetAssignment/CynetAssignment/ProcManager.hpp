#pragma once

#include <filesystem>

class ProcManager
{
public:
    constexpr static char proc_directory_path_name[] = "/proc/";
    const std::filesystem::path proc_direcory_path{ proc_directory_path_name };

public:
    ProcManager() = default;
    virtual ~ProcManager() = default;

    void run();

private:
    static bool isNumber(const std::string& s);

    void RefreshProcessList();
    void PrintProcess(); // TODO (ASK): move to process
    void CheckIfToStop();
    void SleepSomeTime();
};

