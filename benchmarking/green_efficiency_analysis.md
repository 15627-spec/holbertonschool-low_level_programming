# Green Efficiency Analysis

## Measurement Methodology

I measured execution time with `clock()` from `<time.h>`. In each program I take a reading before the work and another one after it. I subtract the two and divide by `CLOCKS_PER_SEC` to get seconds. It works like checking a watch when you walk into work and again when you leave. Both programs were compiled with `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-long-long`.

`baseline_loop.c` runs 100,000,000 iterations. I ran it three times in a row and recorded each output exactly as printed in `baseline_loop-metrics.md`. The pipeline program works on 50,000 numbers in three stages (build, process, reduce) and prints the time of each stage and the total. `clock()` measures CPU time, not real time.

## Observed Performance Differences

The three runs of `baseline_loop` took 0.229590 s, 0.234656 s and 0.235113 s. The average is 0.233120 s, about 2.3 ns per iteration. The gap between the fastest and slowest run is 0.005523 s, about 2.4%. The times are close but not identical, as expected.

The pipeline is much smaller. In one run the total was 0.001152 s: BUILD_DATA took 0.000579 s, PROCESS 0.000411 s and REDUCE 0.000154 s. In another run the total was 0.000741 s (0.000353 s, 0.000238 s and 0.000147 s). BUILD_DATA was the biggest part both times, and the two totals are about 55% apart, much more variation than the baseline loop showed.

## Relation Between Runtime and Energy Consumption

I did not measure energy, so I make no numerical claims about it. The basic formula is energy equals average power multiplied by time. If the power stays about the same, a program that runs for less time uses less energy. Under that assumption, the baseline loop would use roughly 200 times more energy than the pipeline, but I did not check that the power was the same.

## Limitations of the Experiment

- **No energy measurement.** I only recorded time, so the link to energy is an assumption.
- **Very short runs.** The pipeline stages last a fraction of a millisecond, so one reading is not reliable.
- **Few runs.** Three baseline runs and two pipeline runs are not enough for a solid average on this machine.

## Practical Engineering Takeaway

Measure first, and repeat each measurement. The baseline loop gave stable times, but the very short pipeline did not, so a time is only trustworthy once you know how much it changes between runs. Building the dataset took the biggest share in the pipeline, so that is the first place to look for improvement.