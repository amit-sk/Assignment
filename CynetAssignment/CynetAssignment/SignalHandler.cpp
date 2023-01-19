#include <iostream> // TODO (ASK)
#include <cassert>
#include <stdexcept>
#include "SignalHandler.hpp"

SignalHandler::SignalHandler(std::vector<std::shared_ptr<SignalCallback>> callbacks) :
    _callbacks(std::move(callbacks)),
    _wait_set(get_signals_set(get_signal_nums(_callbacks)))
{
    RegisterRequiredSignals();
}

std::vector<uint32_t> SignalHandler::get_signal_nums(const std::vector<std::shared_ptr<SignalCallback>>& callbacks)
{
    std::vector<uint32_t> signals;
    for (const auto& callback : callbacks)
    {
        signals.push_back(callback->get_signal());
    }
    return signals;
}

sigset_t SignalHandler::get_signals_set(const std::vector<uint32_t>& signals)
{
    sigset_t sigset;
    assert(0 == sigemptyset(&sigset));

    for (const uint32_t signal : signals)
    {
        assert(0 == sigaddset(&sigset, signal));
    }
    return sigset;
}

void SignalHandler::RegisterRequiredSignals()
{
    assert(0 == pthread_sigmask(SIG_SETMASK, &_wait_set, NULL));
}

void SignalHandler::ListenForSignalsAndHandle()
{
    siginfo_t siginfo{ 0 };
    int sig_no = 0;

    sig_no = sigwaitinfo(&_wait_set, &siginfo);
    if (sig_no > 0)
    {
        std::cout << "signal received " << std::to_string(sig_no) << '\n';
        for (const auto& callback : _callbacks)
        {
            if (callback->get_signal() == sig_no)
            {
                callback->OnSignal();
            }
        }
    }
    else
    {
        throw std::runtime_error("sigwaitinfo");
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

