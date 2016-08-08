
#include "gmock/gmock.h"
#include "lambda.hpp"

using namespace lambda;
using namespace lambda::factory;

TEST(lambda, show) { printer << vector(1, 2, 3, 4) << "\n"; }
