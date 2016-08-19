
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

TEST(lambda, stream1) {
    display << (stream(vector(1, 2, 3, 4)) | map(plus(1)) | filter(less(4)) | fold(0, plus));
}

TEST(lambda, fold) { ASSERT_EQ(31, stream(vector(1, 2, 3, 4, 6, 7, 8)) | fold(0, plus)); }

TEST(lambda, sum) { ASSERT_EQ(31, stream(vector(1, 2, 3, 4, 6, 7, 8)) | sum); }

TEST(lambda, ints_range) {
    auto s = ints(0, 10);
    while (auto val = s.next()) {
        display << val << '\n';
    }
}

TEST(lambda, take_ints) {
    auto s = ints(0) | map(multiplies(2)) | take(20);
    while (auto val = s.next()) {
        display << val << '\n';
    }
}
