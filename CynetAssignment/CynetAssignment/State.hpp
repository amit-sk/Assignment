#pragma once

#include <memory>
#include <mutex>

namespace _private
{
    static std::unique_ptr<bool> _is_on;
    static std::unique_ptr<std::mutex> _mtx;
}

struct State
{
public:
    static void initialize();

    static bool is_on();
    static void turn_off();
};

