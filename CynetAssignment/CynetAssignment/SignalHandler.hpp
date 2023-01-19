#pragma once

#include <csignal>
#include <map>
#include <functional>

class SignalHandler
{
public:
    explicit SignalHandler(std::map<uint8_t, std::function<void(void)>> handlers);
    virtual ~SignalHandler() = default;

    void ListenForSignalsAndHandle();

private:
    void RegisterRequiredSignals();

    static sigset_t get_signals_set(const std::vector<uint8_t>& signals);
    static std::vector<uint8_t> get_signal_nums(const std::map<uint8_t, std::function<void(void)>>& handlers);

    static void OnCtrlC(int signal);
    static void OnPkill(int signal);

private:
    sigset_t _wait_set;
    std::map<uint8_t, std::function<void(void)>> _handlers;
};

