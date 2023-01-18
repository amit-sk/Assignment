#include <string>
#include <iostream>

#include "StringUtils.hpp"
#include "Process.hpp"
#include "ProcManager.hpp"

ProcManager::ProcManager() :
    _is_running(true)
{}

void ProcManager::turn_off()
{
    _is_running = false;
}

void ProcManager::run()
{
    // TODO (ASK): iterate running processes - updated list. print data for each.
    // check for events from main thread

    // while is running
    for (auto const& proc_entry : std::filesystem::directory_iterator{ proc_direcory_path })
    {
        if (StringUtils::isNumber(proc_entry.path().filename()))
        {
            std::cout << Process{static_cast<uint16_t>(std::stoi(proc_entry.path().filename()))}.Serialize() << '\n';
        }
    }
}
