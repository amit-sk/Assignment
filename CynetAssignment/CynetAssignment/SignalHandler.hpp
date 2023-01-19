#pragma once

#include <csignal>
#include <vector>
#include <memory>
#include <map>
#include <functional>  // TODO (ASK)

#include "SignalCallback.hpp"

class SignalHandler
{
public:
    explicit SignalHandler(std::vector<std::shared_ptr<SignalCallback>> callbacks);
    virtual ~SignalHandler() = default;

    void ListenForSignalsAndHandle();

private:
    void RegisterRequiredSignals();

    static sigset_t get_signals_set(const std::vector<uint32_t>& signals);
    static std::vector<uint32_t> get_signal_nums(const std::vector<std::shared_ptr<SignalCallback>>& callbacks);

    static void OnCtrlC(int signal);
    static void OnPkill(int signal);

private:
    std::vector<std::shared_ptr<SignalCallback>> _callbacks;
    sigset_t _wait_set;
};

