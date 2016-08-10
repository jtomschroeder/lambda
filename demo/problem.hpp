
#pragma once

#include <iostream>

struct Problem {
    static std::vector<std::function<void()>> problems;
    Problem(std::function<void()> p) { problems.push_back(p); }
};

std::vector<std::function<void()>> Problem::problems;

#define CONCAT_IMPL(X, Y) X##Y
#define CONCAT(X, Y) CONCAT_IMPL(X, Y)

#define PROBLEM(E)                                                                                 \
    void E();                                                                                      \
    Problem CONCAT(P, CONCAT(E, __COUNTER__)){E};                                                  \
    void E()
#define SOLUTION(X, Y)                                                                             \
    std::cout << __FUNCTION__ << " == " << Y << " " << ((X) == (Y) ? "👍" : "👎") << std::endl;

#define PROBLEM_MAIN()                                                                             \
    int main() {                                                                                   \
        for (auto problem : Problem::problems) {                                                   \
            problem();                                                                             \
        }                                                                                          \
        return 0;                                                                                  \
    }
