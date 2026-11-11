# Task 3 – Choose Data Types and Check Type Compatibility

## Objective
Choose suitable C++ types, examine their sizes and ranges, and justify exact currency storage.

## 1. Data type selection
| Value | Recommended type | Reason |
|---|---|---|
| Fare in paise | `long long` | Exact integer currency and safe totals |
| Card balance in paise | `long long` | Must not become negative and may grow after recharge |
| Hour | `int` | Values are 0–23 |
| Zone | `enum class Zone` | Represents a fixed set of named choices |
| Peak status | `bool` | True or false |
| Passenger initial | `char` | One character |
| Journey count | `long long` | Large network counts |
| Percentage | `int` | Whole-number percentage in this specification |
| Measurement/experimental rupees | `double` | Used only to demonstrate floating-point behaviour |
| Inferred local value | `auto` | Use only when the inferred type is clear |

The exact sizes are implementation-dependent. Run the supplied `task03_datatypes.cpp` on the target compiler and record its `sizeof` output. On many common 64-bit g++ systems, `int` is 4 bytes, `long long` is 8 bytes and `double` is 8 bytes, but your own result is the evidence to report.

## 2. Why integer paise instead of double rupees?
₹10.25 is represented as 1025 paise. Integer addition and multiplication by integer percentages avoid binary floating-point representation error. For a 20% surcharge, calculate `basePaise * 20 / 100`. The given fares are whole rupees, so the percentage result is exact in paise.

## 3. Type compatibility
In an expression containing `int` and `double`, the integer is usually converted to `double` before the arithmetic. In `7 / 2`, both operands are integers, so integer division gives 3; assigning that result to `double` produces 3.0, not 3.5. A `bool` used in arithmetic is promoted to an integer value of 0 or 1. Avoid relying on surprising implicit conversions.

## 4. Integer limits and network collection
`<climits>` provides `INT_MAX`, `INT_MIN`, `LLONG_MAX` and related limits. For a simple upper-bound example using ₹30 per journey:
- 20,000 journeys: ₹600,000.
- 500,000 journeys: ₹15,000,000.
- 3,000,000 journeys: ₹90,000,000.

In paise, these are 60,000,000; 1,500,000,000; and 9,000,000,000 respectively. The last total exceeds the usual 32-bit signed `int` maximum (2,147,483,647), so `long long` is appropriate. Use the actual `INT_MAX` printed by your compiler when explaining your result.

## 5. Precision experiment
The supplied program adds a decimal value repeatedly using `double` and the equivalent integer number of paise using `long long`. Record the displayed difference. Floating-point error depends on the exact value and number of additions; do not claim a fixed error without running the experiment.

## Alternative concept and complexity analysis
With `double` rupees, each addition is **O(1)** and each `double` commonly occupies 8 bytes. With `long long` paise, each addition is also **O(1)** and `long long` commonly occupies 8 bytes. The space per value is therefore commonly equal, but integer paise provides exact arithmetic for the specified currency amounts. A repeated-addition experiment demonstrates any floating-point deviation for the chosen input and n.
