# Task 4 – Control Implicit Conversions

## Objective
Identify implicit conversions and understand how explicit casts and brace initialization make conversions safer.

## Important conversion points
- `double c = a / b;`: `a` and `b` are both `int`, so integer division occurs first. With 7 and 2 the result is 3, then converted to `double` as 3.0.
- `static_cast<double>(a) / b`: `a` becomes 7.0 before division, so the result is 3.5.
- `char ch = 'A' + 2;`: the character literal is promoted to `int` for addition; the result is converted back to `char`, producing `C` on the usual execution character set.
- `ch + 1`: `ch` is promoted to `int`, so the numeric result is 68 on ASCII-compatible systems.
- `bool flag = 5;`: non-zero integer converts to `true`. `boolalpha` prints `true`; before it is enabled, bool normally prints `1`.
- `s < u`: the signed `int` is converted to unsigned for the comparison because the usual arithmetic conversions apply. `-1` becomes a large unsigned value, so the comparison is false for this example and the program prints `s >= u`.

## Predicted output (write this before running)
```text
3 3.5
C 68
1 true
s >= u
```
The exact character result assumes the common ASCII-compatible execution character set used by typical g++ environments.

## Safer code practices
Use `static_cast<double>(a)` when floating-point division is intended. Use brace initialization such as `int count{3};` to reject narrowing conversions like `int x{3.7};`. Validate signed values before converting them to unsigned values. Compile with `-Wall -Wextra` and address warnings rather than suppressing them.

## Alternative concept and complexity analysis
If every conversion were explicit, the program would state the intended type changes using `static_cast`, and brace initialization would reject many narrowing conversions at compile time. Runtime time and memory are normally unchanged: the cast itself does not add a meaningful algorithmic step, so the operations remain **O(1)** with **O(1)** storage. The main benefit is earlier detection of mistakes by the compiler and clearer intent.
