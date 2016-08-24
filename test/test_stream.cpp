
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;
using namespace lambda::factory;
using namespace lambda::streams;

TEST(lambda, stream) {
    auto s = stream(vector(1, 2, 3, 4)) | map(plus(1)) | filter(less(4));
    while (auto val = s.next()) {
        display << val << '\n';
    }
}

TEST(lambda, streaming) {
    ASSERT_EQ(5, stream(vector(1, 2, 3, 4)) | map(plus(1)) | filter(less(4)) | fold(0, plus));
}

TEST(lambda, fold) { ASSERT_EQ(31, stream(vector(1, 2, 3, 4, 6, 7, 8)) | fold(0, plus)); }

TEST(lambda, sum) { ASSERT_EQ(31, stream(vector(1, 2, 3, 4, 6, 7, 8)) | sum); }

TEST(lambda, ints_range) {
    auto s = ints(0, 10);
    auto v = vector(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    for (auto i : v) {
        ASSERT_EQ(some(i), s.next());
    }

    ASSERT_EQ(none, s.next());
}

TEST(lambda, take_ints) {
    auto s = ints(0) | map(multiplies(2)) | take(10);

    auto v = vector(0, 2, 4, 6, 8, 10, 12, 14, 16, 18);

    for (auto i : v) {
        ASSERT_EQ(some(i), s.next());
    }

    ASSERT_EQ(none, s.next());
}

TEST(lambda, collect) {
    ASSERT_EQ(vector(0, 2, 4, 6, 8), ints(0) | map(multiplies(2)) | take(5) | collect());
}
