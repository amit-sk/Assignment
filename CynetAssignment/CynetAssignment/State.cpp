#include "State.hpp"

bool State::is_on()
{
    std::lock_guard<std::mutex> lock(_private::mtx);
    return _private::_is_on;
}

void State::turn_off()
{
    std::lock_guard<std::mutex> lock(_private::mtx);
    _private::_is_on = false;
}
