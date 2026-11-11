# Task 11 – Recommend and Defend the Final Design

## Objective
Recommend a maintainable and accurate design for the current metro network using evidence from earlier tasks.

## Recommended design
1. Store fares, balances and collections in integer paise using `long long`.
2. Use `enum class Zone` for the supported zones.
3. Use named `constexpr` constants for the fixed base fares, surcharge percentage and minimum balance.
4. Use `SmartCard` with a private balance and validated operations.
5. Keep peak-hour detection and fare calculation in separate functions or a fare-policy class.
6. Validate hour, zone and recharge input before calculation.
7. Use a loop over journeys and a repeatable test table for boundary cases.

## Fare revision
For the original three-zone design, change the fare constants in one location, rebuild and rerun all tests. A larger system may load a validated configuration file at startup so authorized fare changes do not require recompilation. The configuration must be checked for missing zones, negative fares and invalid percentages.

## Limitations
The original specification does not provide student/senior concession percentages, concession eligibility verification, refund rules or fare rounding rules for fractional paise. Those require policy decisions before production deployment. A fixed three-zone switch is also less flexible when zones are added frequently.

## Whole-network suitability
The arithmetic per journey remains constant time, and `long long` is suitable for the sample network totals. A production system would also need transaction safety, concurrency handling, durable card storage, audit logs, security and central fare configuration; these are beyond this assignment's small C++ console model.

## Alternative concept and complexity analysis
Loading z fares from a configuration file takes **O(z)** startup time and **O(z)** storage. After loading, a fare lookup is **O(1)** with a suitable indexed table. Compiled-in `constexpr` fares avoid file parsing at startup but require recompilation and redeployment after changes. For a small fixed assignment, `constexpr` is simple and safe; for frequent policy updates, a validated configuration file is more maintainable.
