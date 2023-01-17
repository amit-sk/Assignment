#include "ProcManager.hpp"

#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>

bool ProcManager::isNumber(const std::string &s)
{
    return (not s.empty()) and std::all_of(s.begin(), s.end(), ::isdigit);
}

void ProcManager::run()
{
    // TODO (ASK): iterate running processes - updated list. print data for each.
    // check for events from main thread

    for (auto const& proc_entry : std::filesystem::directory_iterator{ proc_direcory_path })
    {
        if (isNumber(proc_entry.path().filename()))
        {
            std::cout << proc_entry.path().filename() << '\n';
        }
    }
}
