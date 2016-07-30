
#define RANGES_SUPPRESS_IOTA_WARNING
#include <range/v3/all.hpp>
#include <iostream>

#include "lambda.hpp"
using namespace lambda;

/////////////////////////

struct Problem {
    static std::vector<std::function<void()>> problems;
    Problem(std::function<void()> p) { problems.push_back(p); }
};
std::vector<std::function<void()>> Problem::problems;

#define CONCAT_IMPL(X, Y) X##Y
#define CONCAT(X, Y) CONCAT_IMPL(X, Y)

#define PROBLEM(E)                                                                                 \
    void E();                                                                                      \
    Problem CONCAT(E, __COUNTER__){E};                                                             \
    void E()
#define SOLUTION(X, Y)                                                                             \
    std::cout << __FUNCTION__ << " == " << Y << " " << (X == Y ? "👍" : "👎") << std::endl;

/////////////////////////

template <typename Range>
auto sum(Range &&range) {
    return ranges::accumulate(range, 0);
}

const auto multipleOf = curry(flip([](auto x, auto y) { return x % y == 0; }));
const auto even = multipleOf(2);

using namespace ranges;

// Find the sum of all the multiples of 3 or 5 below 1000.
PROBLEM(E1) {
    const auto solution = sum(view::ints(0, 1000) | view::filter(multipleOf(3) || multipleOf(5)));

    SOLUTION(solution, 233168);
}

// By considering the terms in the Fibonacci sequence whose values do not exceed
// four million, find the sum of the even-valued terms.
PROBLEM(E2) {
    auto fibonacci = view::generate([] {
        static uint64_t x = 0, y = 1;
        auto tmp = x;
        x += y;
        std::swap(x, y);
        return tmp;
    });

    const auto solution =
        sum(fibonacci | view::filter(even) | view::take_while(curry(flip(std::less<>{}), 4e6)));

    SOLUTION(solution, 4613732);
}

uint64_t smallest_factor(uint64_t n) {
    auto factors = view::closed_ints(2ull, n) >>= [n](auto i) { return yield_if(n % i == 0, i); };

    return factors.front();
}

uint64_t largest_prime_factor(uint64_t n) {
    const auto p = smallest_factor(n);
    return (p == n) ? n : largest_prime_factor(n / p);
}

// What is the largest prime factor of the number 600851475143?
PROBLEM(E3) { SOLUTION(largest_prime_factor(600851475143), 6857); }

// Find the largest palindrome made from the product of two 3-digit numbers.
PROBLEM(E4) {
    // list comprehension of product of two 3-digit numbers
    auto products = view::ints(100, 1000) >>=
        [](int x) { return view::ints(x, 1000) >>= [=](int y) { return yield(x * y); }; };

    const auto palindrome = [](auto n) -> bool {
        const auto str = std::to_string(n);

        auto front = str.begin();
        auto back = str.rbegin();
        for (; front + (str.size() / 2) != str.end(); front++, back++) {
            if (*front != *back) {
                return false;
            }
        }

        return true;
    };

    const auto solution = max(products | view::filter(palindrome));

    SOLUTION(solution, 906609);
}

uint64_t gcd(uint64_t x, uint64_t y) {
    // Euclidean algorithm
    return (y == 0) ? x : gcd(y, x % y);
}

uint64_t lcm(uint64_t x, uint64_t y) { return (x * y) / gcd(x, y); }

// What is the smallest positive number that is evenly divisible by all of the
// numbers from 1 to 20?
PROBLEM(E5) { SOLUTION(ranges::accumulate(view::closed_ints(1, 20), 1, lcm), 232792560); }

// Find the difference between the sum of the squares of the first one hundred
// natural numbers and the square of the sum.
PROBLEM(E6) {
    const auto square = [](auto i) { return i * i; };

    const auto n = 100;
    const auto solution = square(sum(view::closed_ints(1, n))) -
                          sum(view::closed_ints(1, n) | view::transform(square));

    SOLUTION(solution, 25164150);
}

const auto prime = [](uint64_t x) {
    if (x == 2) {
        return true;
    } else if (x < 2 || even(x)) {
        return false;
    } else {
        for (uint64_t i = 3, end = sqrt(x); i <= end; i += 2) {
            if (multipleOf(i)(x)) {
                return false;
            }
        }
        return true;
    }
};

// What is the 10,001st prime number?
PROBLEM(E7) {
    const auto solution = (view::ints(1) | view::filter(prime) | view::drop(10000)).front();

    SOLUTION(solution, 104743);
}

int main() {
    ranges::for_each(Problem::problems, [](const auto &p) { p(); });
    return 0;
}
