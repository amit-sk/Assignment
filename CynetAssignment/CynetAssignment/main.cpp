#include <iostream>
#include <thread>
#include <csignal> // TODO (ASK)

#include "State.hpp"
#include "SignalHandler.hpp"
#include "ProcManager.hpp"

int main()
{
    SignalHandler signal_handler{ {
        {SIGINT, []() { std::cout << "on ctrl c" << '\n'; }},
    } };
    ProcManager process_manager;

    //std::signal(SIGINT, [](int signal) { State::turn_off(); });
    //std::signal(SIGTERM, [](int signal) { State::turn_off(); });

    std::thread proc_manager_thread(&ProcManager::run, &process_manager);

    signal_handler.ListenForSignalsAndHandle();

    //std::string i;
    //std::cin >> i;

    //std::raise(SIGINT);
    //std::cout << std::boolalpha << (g_should_proc_manager_run) << '\n';

    std::cout << "Done" << '\n';
    //process_manager.turn_off();
    proc_manager_thread.join();
    return 0;
}