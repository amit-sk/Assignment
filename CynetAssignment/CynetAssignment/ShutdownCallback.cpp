#include <iostream> // TODO (ASK)

#include "State.hpp"
#include "ShutdownCallback.hpp"

void ShutdownCallback::OnSignal()
{
    std::cout << "In shutdown callback" << '\n';
    State::turn_off();
}

