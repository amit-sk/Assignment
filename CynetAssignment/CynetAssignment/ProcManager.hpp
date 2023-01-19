#pragma once

#include <filesystem>
#include <mutex>

static std::mutex mtx;
static bool _should_proc_manager_run = true;

class ProcManager
{
private:
    constexpr static char proc_directory_path_name[] = "/proc/";
    const std::filesystem::path proc_direcory_path{ proc_directory_path_name };

public:
    ProcManager() = default;
    virtual ~ProcManager() = default;

    void run();
    static void turn_off();
    static bool is_on();

private:
    void RefreshProcessList();
    void PrintProcess(); // TODO (ASK): move to process
    void CheckIfToStop();
    void SleepSomeTime();
};

