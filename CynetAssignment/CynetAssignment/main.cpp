#include <iostream>
#include <thread>
#include <csignal> // TODO (ASK)

#include "State.hpp"
#include "SignalHandler.hpp"
#include "ProcManager.hpp"
#include "ShutdownCallback.hpp"

int main()
{
    State::initialize();

    auto ctrl_c_cb = std::make_shared<ShutdownCallback>(static_cast<uint32_t>(SIGINT));
    auto pkill_cb = std::make_shared<ShutdownCallback>(static_cast<uint32_t>(SIGTERM));
    SignalHandler signal_handler{ { ctrl_c_cb, pkill_cb } };
    ProcManager process_manager;

    std::thread proc_manager_thread(&ProcManager::run, &process_manager);

    signal_handler.ListenForSignalsAndHandle();

    std::cout << "Done" << '\n';
    proc_manager_thread.join();
    return 0;
}