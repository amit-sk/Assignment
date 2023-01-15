#include <cstdio>
#include <thread>

#include "SignalHandler.hpp"
#include "ProcManager.hpp"

int main()
{
    SignalHandler signal_handler;
    ProcManager process_manager;

    std::thread proc_manager_thread(&ProcManager::run, &process_manager);
    proc_manager_thread.join();
    printf("hello from CynetAssignment!\n");
    return 0;
}