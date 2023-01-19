#pragma once

#include <cstdint>

class SignalCallback
{
public:
    explicit SignalCallback(uint32_t signal);
    virtual ~SignalCallback() = default;

    uint32_t get_signal() const;

    virtual void OnSignal() = 0;

private:
    uint32_t _signal;
};

