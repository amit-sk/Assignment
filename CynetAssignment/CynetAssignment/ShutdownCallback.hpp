#pragma once

#include "SignalCallback.hpp"

class ShutdownCallback : public SignalCallback
{
public:
    using SignalCallback::SignalCallback;
    virtual ~ShutdownCallback() = default;

    virtual void OnSignal();
};

