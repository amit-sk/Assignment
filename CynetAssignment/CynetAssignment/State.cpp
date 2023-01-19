#include "State.hpp"

#include <cassert>

void State::initialize()
{
    assert(_private::_mtx.get() == nullptr and _private::_is_on.get() == nullptr);
    _private::_is_on = std::make_unique<bool>(true);
    _private::_mtx = std::make_unique<std::mutex>();
}

bool State::is_on()
{
    assert(_private::_mtx.get() != nullptr and _private::_is_on.get() != nullptr);
    std::lock_guard<std::mutex> lock(*_private::_mtx);
    return *_private::_is_on;
}

void State::turn_off()
{
    assert(_private::_mtx.get() != nullptr and _private::_is_on.get() != nullptr);
    std::lock_guard<std::mutex> lock(*_private::_mtx);
    *_private::_is_on = false;
}
