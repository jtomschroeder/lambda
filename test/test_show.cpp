
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;

TEST(lambda, show) { printer << $.map($.vector(1, 2, 3, 4), plus(1)) << "\n"; }
