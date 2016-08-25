
#pragma once

#include <vector>

#include "lambda.hpp"

struct Problem {
    static std::vector<std::function<void()>> problems;
    explicit Problem(std::function<void()> p) { problems.push_back(p); }
};

#define CONCAT_IMPL(X, Y) X##Y
#define CONCAT(X, Y) CONCAT_IMPL(X, Y)

#define PROBLEM(E)                                                                                 \
    void E();                                                                                      \
    Problem CONCAT(P, CONCAT(E, __COUNTER__)){E};                                                  \
    void E()

namespace problem {
template <class T, class U>
void solution(std::string function, const T &t, const U &u) {
    lambda::display << function << ": " << t << " == " << u << " " << (t == u ? "👍" : "👎") << "\n";
}
}

#define SOLUTION(X, Y) problem::solution(__FUNCTION__, (X), (Y))

#define PROBLEM_MAIN()                                                                             \
    std::vector<std::function<void()>> Problem::problems;                                          \
    int main() {                                                                                   \
        for (auto problem : Problem::problems) {                                                   \
            problem();                                                                             \
        }                                                                                          \
        return 0;                                                                                  \
    }
