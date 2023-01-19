#include <iostream> // TODO (ASK)
#include "SignalHandler.hpp"

SignalHandler::SignalHandler(std::map<uint8_t, std::function<void(void)>> handlers) :
    _handlers(std::move(handlers)),
    _wait_set(get_signals_set(get_signal_nums(handlers)))
{
    RegisterRequiredSignals();
}

std::vector<uint8_t> SignalHandler::get_signal_nums(const std::map<uint8_t, std::function<void(void)>>& handlers)
{
    std::vector<uint8_t> signals;
    for (const auto&[sig, _] : handlers)
    {
        signals.push_back(sig);
    }
    return signals;
}

sigset_t SignalHandler::get_signals_set(const std::vector<uint8_t>& signals)
{
    sigset_t sigset;
    sigemptyset(&sigset);

    for (const uint8_t signal : signals)
    {
        sigaddset(&sigset, signal);
    }
    return sigset;
}

void SignalHandler::RegisterRequiredSignals()
{
    pthread_sigmask(SIG_SETMASK, &_wait_set, NULL);
}

void SignalHandler::ListenForSignalsAndHandle()
{
    siginfo_t siginfo{ 0 };
    int sig_no = 0;
    while (true)
    {
        sig_no = sigwaitinfo(&_wait_set, &siginfo);
        if (sig_no > 0)
        {
            // callback
            std::cout << "signal received " << std::to_string(sig_no) << '\n';
            _handlers.at(sig_no)();
        }
    }
}

void SignalHandler::OnCtrlC(int signal)
{
    std::cout << "OnCtrlC" << '\n';
}

void SignalHandler::OnPkill(int signal)
{
    std::cout << "OnPkill" << '\n';
}

