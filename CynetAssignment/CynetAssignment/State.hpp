#pragma once

#include <mutex>

namespace _private
{
    static volatile bool _is_on = true;
    static std::mutex mtx;
}

struct State
{
public:
    static bool is_on();
    static void turn_off();
};

