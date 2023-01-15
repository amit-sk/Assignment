#pragma once

class ProcManager
{
public:
    ProcManager() = default;
    virtual ~ProcManager() = default;

    void run();

private:
    void RefreshProcessList();
    void PrintProcess(); // TODO (ASK): move to process
    void CheckIfToStop();
    void SleepSomeTime();
};

