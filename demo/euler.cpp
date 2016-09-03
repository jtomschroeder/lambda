
#include <cmath>

#include "problem.hpp"

#include "lambda.hpp"
#include "lambda/stream.hpp"

using namespace lambda;
using namespace lambda::streams;

// Find the sum of all the multiples of 3 or 5 below 1000.
PROBLEM(E1) {
    let solution = ints(0, 1000) | filter(multipleOf(3) || multipleOf(5)) | sum;
    SOLUTION(solution, 233168);
}

// By considering the terms in the Fibonacci sequence whose values do not exceed
// four million, find the sum of the even-valued terms.
PROBLEM(E2) {
    let fibonacci = generator([] {
        static uint64_t x = 0, y = 1;
        auto tmp = x;
        x += y;
        std::swap(x, y);
        return tmp;
    });

    let solution = fibonacci | filter(even) | take_while(less(4e6)) | sum;
    SOLUTION(solution, 4613732);
}

uint64_t smallest_factor(uint64_t n) {
    auto factors = closed_ints(2ull, n) | filter([n](auto i) { return n % i == 0; });
    return *factors.next();
}

uint64_t largest_prime_factor(uint64_t n) {
    const auto p = smallest_factor(n);
    return (p == n) ? n : largest_prime_factor(n / p);
}

// What is the largest prime factor of the number 600851475143?
PROBLEM(E3) {
    let solution = largest_prime_factor(600851475143);
    SOLUTION(solution, 6857);
}

// Find the largest palindrome made from the product of two 3-digit numbers.
PROBLEM(E4) {
    // list comprehension of product of two 3-digit numbers
    // auto products = ints(100, 1000) >>=
    //     [](int x) { return ints(x, 1000) >>= [=](int y) { return yield(x * y); }; };

    // list comprehension of product of two 3-digit numbers
    let products = stream([]() -> Maybe<int> {
        static int x = 100, y = 100;
        if (x >= 1000) {
            return none;
        }

        if (y >= 1000) {
            y = ++x;
        }

        return x * y++;
    });

    const auto palindrome = [](auto n) {
        const auto str = std::to_string(n);

        auto front = str.begin();
        auto back = str.rbegin();
        for (; front + (str.size() / 2) != str.end(); ++front, ++back) {
            if (*front != *back) {
                return false;
            }
        }

        return true;
    };

    let max = [](auto x, auto y) { return std::max(x, y); };

    let solution = products | filter(palindrome) | fold(0, max);
    SOLUTION(solution, 906609);
}

// What is the smallest positive number that is evenly divisible by all of the
// numbers from 1 to 20?
PROBLEM(E5) {
    let solution = closed_ints(1ull, 20ull) | fold(1, lcm);
    SOLUTION(solution, 232792560);
}

// Find the difference between the sum of the squares of the first one hundred
// natural numbers and the square of the sum.
PROBLEM(E6) {
    let n = 100;
    let solution = square(closed_ints(1, n) | sum) - (closed_ints(1, n) | map(square) | sum);

    SOLUTION(solution, 25164150);
}

let prime = [](auto x) {
    if (x == 2) {
        return true;
    }

    if (x < 2 || even(x)) {
        return false;
    }

    using I = std::remove_reference_t<std::remove_const_t<decltype(x)>>;
    for (I i = 3, end = sqrt(x); i <= end; i += 2) {
        if (multipleOf(i, x)) {
            return false;
        }
    }

    return true;
};

// What is the 10,001st prime number?
PROBLEM(E7) {
    auto solution = ints(1) | filter(prime) | drop(10000);
    SOLUTION(solution.next(), some(104743));
}

PROBLEM_MAIN()
