#pragma once

class SignalHandler
{
public:
    SignalHandler();
    virtual ~SignalHandler() = default;

    void ListenForSignalsAndHandle();

private:
    void RegisterRequiredSignals();
    // void CreateThread();

    void OnCtrlC();
    void OnPkill();
};

