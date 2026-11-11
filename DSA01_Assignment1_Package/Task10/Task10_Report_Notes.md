# Task 10 – Compare Expectations with Execution

## Objective
Compare floating-point and integer-paise totals, test integer overflow and record compiler warnings.

## Calculation using ₹10 per journey (illustrative fixed-fare experiment)
| Journeys | Total in rupees | Total in paise |
|---:|---:|---:|
| 20,000 | ₹200,000 | 20,000,000 |
| 500,000 | ₹5,000,000 | 500,000,000 |
| 3,000,000 | ₹30,000,000 | 3,000,000,000 |

The ₹10 fare is an explicit experimental assumption for this comparison, not the maximum possible fare. At 3,000,000 journeys, 3,000,000,000 paise exceeds the usual signed 32-bit `int` maximum of 2,147,483,647. `long long` can safely hold this total on standard implementations with at least 64-bit range. The rupee total of 30,000,000 fits a 32-bit signed int, but using `int` for paise does not.

## What to record
Run `task10_totals.cpp` and record its integer-paise and double-rupee output. The program also prints the compiler's `INT_MAX` and `LLONG_MAX`. Do not claim a measured rounding difference unless the output shows one. `double` has finite binary precision and can represent many decimal fractions only approximately.

## Compiler warnings
Compile each program with `-std=c++17 -Wall -Wextra`. Record the exact warning text and the source line. A warning is compiler-specific; do not invent warnings. Fix unused variables, suspicious conversions or missing returns where applicable.

## Alternative concept and complexity analysis
For n journeys, accumulating into `int`, `long long` or `double` takes **O(n)** total time and **O(1)** extra space. Each addition is **O(1)**. `int` can overflow when the total exceeds its range; signed overflow is undefined behaviour in C++. `long long` provides a much larger integer range. `double` avoids integer overflow for these values but can introduce rounding representation error. The variable sizes should be measured with `sizeof` on the target compiler.
