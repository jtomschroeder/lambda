
#include <benchmark/benchmark.h>

#include <lambda.hpp>
#include <lambda/stream.hpp>

using namespace lambda;
using namespace lambda::streams;

class LambdaPerf : public benchmark::Fixture {};

BENCHMARK_F(LambdaPerf, Streams)(benchmark::State &state) {
    while (state.KeepRunning()) {
        let solution = ints(0, 1000) | filter(multipleOf(3) || multipleOf(5)) | sum;
        benchmark::DoNotOptimize(solution);
    }
}

BENCHMARK_MAIN();
