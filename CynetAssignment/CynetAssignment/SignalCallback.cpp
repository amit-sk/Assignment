#include "SignalCallback.hpp"

SignalCallback::SignalCallback(uint32_t signal) :
    _signal(signal)
{}

uint32_t SignalCallback::get_signal() const
{
    return _signal;
}
