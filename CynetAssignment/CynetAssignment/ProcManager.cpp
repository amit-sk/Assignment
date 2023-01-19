#include <string>
#include <iostream>

#include "State.hpp"
#include "StringUtils.hpp"
#include "Process.hpp"
#include "ProcManager.hpp"

void ProcManager::run()
{
    std::string processes_desc;

    while (State::is_on())
    {
        processes_desc = "";
        for (auto const& proc_entry : std::filesystem::directory_iterator{ proc_direcory_path })
        {
            if (StringUtils::isNumber(proc_entry.path().filename()))
            {
                processes_desc += Process{static_cast<uint16_t>(std::stoi(proc_entry.path().filename()))}.Serialize() + "\n";
            }
        }
        std::cout << processes_desc << '\n';
    }
    std::cout << "Shutting down" << '\n';
}
