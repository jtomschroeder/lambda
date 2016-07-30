
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;

static auto mul(int x, int y, int z) { return x * y * z; }

TEST(lambda, curry) {
    auto curried = curry(mul);
    ASSERT_EQ(curried(3, 4, 5), 60);
    ASSERT_EQ(curried(3)(4, 5), 60);
    ASSERT_EQ(curried(3)(4)(5), 60);
}

struct Thing {
    auto fn(int x, int y, int z) { return x + y + z; }

    auto cfn(int x, int y, int z) const { return x + y + z; }
} static thing;

TEST(lambda, curry_mem_fn) {
    auto curried = curry(&Thing::fn);
    ASSERT_EQ(curried(&thing, 1, 2, 3), 6);
    ASSERT_EQ(curried(&thing)(1, 2, 3), 6);
    ASSERT_EQ(curried(&thing)(1)(2, 3), 6);
    ASSERT_EQ(curried(&thing)(1)(2)(3), 6);
}

TEST(lambda, curry_const_mem_fn) {
    auto curried = curry(&Thing::cfn);
    ASSERT_EQ(curried(&thing, 1, 2, 3), 6);
    ASSERT_EQ(curried(&thing)(1, 2, 3), 6);
    ASSERT_EQ(curried(&thing)(1)(2, 3), 6);
    ASSERT_EQ(curried(&thing)(1)(2)(3), 6);
}
