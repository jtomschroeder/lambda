
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;

auto id(int n) { return some(n); }
auto id_s(int n) { return some(std::to_string(n)); }

TEST(lambda, maybe) {
    let num = some(1024);
    ASSERT_TRUE(bool(num));

    let n = num >> id >> id_s >> ([](auto s) { return some(s + "!"); });

    printer << n << 1 << "\n";

    ASSERT_EQ("1024!", *n);
}
