#include <string>
#include <iostream>

#include "State.hpp"
#include "StringUtils.hpp"
#include "Process.hpp"
#include "ProcManager.hpp"

void ProcManager::turn_off()
{
    std::lock_guard<std::mutex> lock(mtx);
    _should_proc_manager_run = false;
}

bool ProcManager::is_on()
{
    std::lock_guard<std::mutex> lock(mtx);
    return _should_proc_manager_run;
}

void ProcManager::run()
{
    // TODO (ASK): iterate running processes - updated list. print data for each.
    // check for events from main thread
    std::string processes_desc;

    while (State::is_on())
    {
        processes_desc = "";
        for (auto const& proc_entry : std::filesystem::directory_iterator{ proc_direcory_path })
        {
            if (not State::is_on())
                break;
            if (StringUtils::isNumber(proc_entry.path().filename()))
            {
                //processes_desc += Process{static_cast<uint16_t>(std::stoi(proc_entry.path().filename()))}.Serialize() + "\n";
            }
        }
        //std::cout << processes_desc << '\n';
    }
    std::cout << "Shutting down" << '\n';
}
