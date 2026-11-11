# Task 2 – Use Tokens, Keywords, Identifiers and Constants Correctly

## Objective
Define fare values and limits in one place and use C++ tokens and constants safely.

## 1. Five kinds of tokens
| Token kind | Meaning | Examples in this assignment |
|---|---|---|
| Keywords | Reserved words with language meaning | `int`, `class`, `if`, `return`, `switch`, `enum` |
| Identifiers | Programmer-defined names | `SmartCard`, `balancePaise`, `calculateFare` |
| Constants / literals | Fixed values written in code | `20`, `5000`, `'A'`, `true` |
| Operators | Symbols that perform operations | `+`, `-`, `*`, `/`, `>=`, `&&`, `+=` |
| Punctuators | Symbols that structure code | `{ } ( ) ; , [ ]` |

## 2. `#define`, `const` and `constexpr`
- `#define` is a preprocessor substitution. It has no C++ type and does not obey normal C++ scope in the same way as a variable.
- `const` declares a typed object that cannot be modified after initialization. Its value need not always be known at compile time.
- `constexpr` declares a value or function that can be evaluated at compile time when its inputs permit it. It is typed and participates in normal C++ scope and type checking.

`constexpr` is preferred for fixed fare values because it is typed, scoped, checked by the compiler and suitable for compile-time expressions.

## 3. Zones: `enum` and `enum class`
An unscoped `enum` exposes enumerator names into the surrounding scope and can convert to an integer more freely. `enum class Zone { Inner, Middle, Outer };` scopes names under `Zone` and does not implicitly convert to `int`. This reduces accidental mixing of zone values with unrelated integers.

## 4. Identifier naming conventions
Identifiers must not be C++ keywords, must not begin with a digit, and should use meaningful names. This package uses `PascalCase` for class and enum names (`SmartCard`, `Zone`) and `camelCase` for variables and functions (`balancePaise`, `calculateFare`). Constants use uppercase words separated by underscores (`MIN_BALANCE_PAISE`).

## Example constants
`constexpr long long INNER_FARE_PAISE = 1000;`
`constexpr long long MIDDLE_FARE_PAISE = 2000;`
`constexpr long long OUTER_FARE_PAISE = 3000;`
`constexpr int PEAK_SURCHARGE_PERCENT = 20;`
`constexpr long long MIN_BALANCE_PAISE = 5000;`

## Alternative concept and complexity analysis
If `#define` macros were used, fare values could be substituted textually, for example `#define INNER_FARE_PAISE 1000`. A macro has no declared C++ type and does not provide normal variable scope or type checking. A `constexpr` value has a type and scope. In simple use, both normally require no separate runtime storage, and neither changes the fare calculation's **O(1)** running time. `constexpr` is safer and easier to debug; macros are more prone to precedence and naming mistakes.
