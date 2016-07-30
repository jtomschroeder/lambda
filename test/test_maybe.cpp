
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;

auto id(int n) { return some(std::to_string(n)); }

TEST(lambda, maybe) {
    let num = some(1024);
    ASSERT_TRUE(bool(num));

    let n = num >= id >= ([](auto s) { return some(s + "!"); });
    ASSERT_EQ("1024!", *n);
}
