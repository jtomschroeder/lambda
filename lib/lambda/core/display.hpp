
#pragma once

#include "show.hpp"
#include <iostream>

namespace lambda {

class Display {
public:
    static Display get() {
        static Display p;
        return p;
    }

    Display() = default;

    Display &operator<<(std::string s) {
        std::cout << s;
        return *this;
    }
};

static auto display = Display::get();

template <class T>
Display &operator<<(Display &display, const T value) {
    display << show(value);
    return display;
}

} /* lambda */
